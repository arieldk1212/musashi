#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"
#include "shader.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace musashi {

class Model {
 public:
  explicit Model(const std::filesystem::path& path);

  void Draw(Shader& shader);

 private:
  void LoadModel(const std::filesystem::path& path);
  void ProcessNode(aiNode* node, const aiScene* scene);
  Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
  std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                            std::string type_name);
  unsigned int TextureFromFile(const char* path);

  std::string directory_;
  std::vector<Mesh> meshes_;
  std::vector<Texture> textures_loaded_;
};

}  // namespace musashi

#endif