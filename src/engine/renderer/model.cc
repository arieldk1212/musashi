#include "model.h"

#include <print>

#include <assimp/Importer.hpp>
#include <assimp/material.h>

#include "vendor/stb_image.h"

namespace musashi {

Model::Model(const std::filesystem::path& path) {
  LoadModel(path);
}

void Model::Draw(Shader& shader) {
  for (auto& mesh : meshes_) {
    mesh.Draw(shader);
  }
}

void Model::LoadModel(const std::filesystem::path& path) {
  Assimp::Importer importer;
  // Triangulate - Transform all primitive shapes into triangles
  // Flip UVS - Flip textures upside down.
  // More options: aiProcess_GenNormals, aiProcess_SplitLargeMeshes,
  // aiProcess_OptimizeMeshes
  const aiScene* scene =
      importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |
                                  aiProcess_GenSmoothNormals);

  if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      scene->mRootNode == nullptr) {
    std::println("ERROR::ASSIMP::{}", importer.GetErrorString());
    return;
  }

  auto path_string = path.string();
  directory_ = path_string.substr(0, path_string.find_last_of('/'));

  ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
    auto* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.emplace_back(ProcessMesh(mesh, scene));
  }

  for (unsigned int i = 0; i < node->mNumChildren; ++i) {
    ProcessNode(node->mChildren[i], scene);
  }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
  std::vector<Vertex> vertices;
  std::vector<Texture> textures;
  std::vector<uint32_t> indices;

  for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex{};

    glm::vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.position = vector;

    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;
    }

    if (mesh->HasTextureCoords(0)) {
      glm::vec2 vector;
      vector.x = mesh->mTextureCoords[0][i].x;
      vector.y = mesh->mTextureCoords[0][i].y;
      vertex.tex_coords = vector;
    } else {
      vertex.tex_coords = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
    auto face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; ++j) {
      indices.push_back(face.mIndices[j]);
    }
  }

  if (mesh->mMaterialIndex >= 0) {
    auto* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuse_maps = LoadMaterialTextures(
        material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

    std::vector<Texture> specular_maps = LoadMaterialTextures(
        material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

    std::vector<Texture> normal_maps =
        LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
    std::vector<Texture> height_maps =
        LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), height_maps.begin(), height_maps.end());
  }

  return Mesh{vertices, indices, textures};
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat,
                                                 aiTextureType type,
                                                 std::string type_name) {
  std::vector<Texture> textures;

  for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
    aiString str;
    mat->GetTexture(type, i, &str);
    bool skip{false};

    for (auto& texture_loaded : textures_loaded_) {
      if (std::strcmp(texture_loaded.path.data(), str.C_Str()) == 0) {
        textures.push_back(texture_loaded);
        skip = true;
        break;
      }
    }

    if (!skip) {
      Texture texture;
      texture.id = TextureFromFile(str.C_Str());
      texture.type = std::move(type_name);
      texture.path = str.C_Str();
      textures.push_back(texture);
      textures_loaded_.push_back(texture);
    }
  }
  return textures;
}

unsigned int Model::TextureFromFile(const char* path) {
  std::string filename = std::string(path);
  filename = directory_ + '/' + filename;

  unsigned int texture_id{0};
  glGenTextures(1, &texture_id);

  int width{0};
  int height{0};
  int nr_components{0};

  unsigned char* data =
      stbi_load(filename.c_str(), &width, &height, &nr_components, 0);

  if (data != nullptr) {
    GLenum format{};
    if (nr_components == 1)
      format = GL_RED;
    else if (nr_components == 3)
      format = GL_RGB;
    else if (nr_components == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

  } else {
    std::println("Texture failed to load at path: {}", path);
    stbi_image_free(data);
  }

  return texture_id;
}

}  // namespace musashi