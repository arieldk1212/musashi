#include "mesh.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace musashi {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices,
           std::vector<Texture> textures)
    : vertices_(std::move(vertices)),
      indices_(std::move(indices)),
      textures_(std::move(textures)) {
  SetupMesh();
}

void Mesh::SetupMesh() {
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex),
               vertices_.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int),
               indices_.data(), GL_STATIC_DRAW);

  // vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  // vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, normal));
  // vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, tex_coords));

  glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader) {
  // names can vary on different implementations, change accordingly
  uint32_t diffuse_nr{1};
  uint32_t specular_nr{1};
  uint32_t normal_nr{1};
  uint32_t height_nr{1};
  for (unsigned int i = 0; i < textures_.size(); i++) {
    glActiveTexture(GL_TEXTURE0 +
                    i);  // activate proper texture unit before binding
    // retrieve texture number (the N in diffuse_textureN)
    std::string number;
    std::string name = textures_[i].type;
    if (name == "texture_diffuse") {
      number = std::to_string(diffuse_nr++);
    } else if (name == "texture_specular") {
      number = std::to_string(specular_nr++);
    } else if (name == "texture_normal") {
      number = std::to_string(normal_nr++);
    } else if (name == "texture_height") {
      number = std::to_string(height_nr++);
    }

    name.append(number);
    shader.SetInt(name, i);
    glBindTexture(GL_TEXTURE_2D, textures_[i].id);
  }

  // draw mesh
  glBindVertexArray(vao_);
  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT,
                 0);  // changed from 0
  glBindVertexArray(0);

  glActiveTexture(GL_TEXTURE0);
}

};  // namespace musashi
