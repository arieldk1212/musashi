#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>

#include "Renderer/Shader.h"

namespace Musashi {

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec3 TexCoords;
};

struct Texture {
  uint32_t id;
  std::string type;
};

class Mesh {
public:
  Mesh(const std::vector<Vertex> &vertices,
       const std::vector<uint32_t> &indices,
       const std::vector<Texture> &textures);

  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
  std::vector<Texture> textures;

  void Draw(Shader &shader);

private:
  void setupMesh();

  uint32_t vao_;
  uint32_t vbo_;
  uint32_t ebo_;
};

}; // namespace Musashi

#endif