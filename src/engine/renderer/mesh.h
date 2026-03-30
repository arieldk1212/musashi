#ifndef MESH_H_
#define MESH_H_

#include "shader.h"

#include <string>
#include <vector>

namespace musashi {

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex_coords;
};

struct Texture {
  uint32_t id;
  std::string type;
  std::string path;
};

class Mesh {
 public:
  Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices,
       std::vector<Texture> textures);

  void Draw(Shader& shader);

 private:
  void SetupMesh();

  uint32_t vao_{0};
  uint32_t vbo_{0};
  uint32_t ebo_{0};
  std::vector<Vertex> vertices_;
  std::vector<uint32_t> indices_;
  std::vector<Texture> textures_;
};

};  // namespace musashi

#endif