#ifndef MESH_H_
#define MESH_H_

#include <array>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace musashi {

struct Vertex {
  glm::vec3 pos;
  glm::vec2 uv;
};

class VertexData {
 public:
  VertexData() = default;
  ~VertexData();

  void Init(const std::array<Vertex, 4>& vertices,
            const std::array<uint32_t, 6>& indices = {});

  void Bind() const;
  void Draw() const;
  void Destroy();

  static void Unbind();
  static void SetupLayout();

 private:
  uint32_t vao_{0};
  uint32_t vbo_{0};
  uint32_t ibo_{0};
  uint32_t index_count_{0};
  uint32_t vertices_count_{0};
};

struct Mesh {
  VertexData vertex;
  std::array<Vertex, 4> data;
  std::array<uint32_t, 6> indices;

  Mesh(const std::array<Vertex, 4>& data,
       const std::array<uint32_t, 6>& indices)
      : data(data),
        indices(indices) {
    vertex.Init(data, indices);
  }
};

struct Quad2D {
  static constexpr std::array<Vertex, 4> kData = {
      {{.pos = glm::vec3(0.5f, 0.5f, 0.0f), .uv = glm::vec2(1.0f, 1.0f)},
       {.pos = glm::vec3(0.5f, -0.5f, 0.0f), .uv = glm::vec2(1.0f, 0.0f)},
       {.pos = glm::vec3(-0.5f, -0.5f, 0.0f), .uv = glm::vec2(0.0f, 0.0f)},
       {.pos = glm::vec3(-0.5f, 0.5f, 0.0f), .uv = glm::vec2(0.0f, 1.0f)}}};

  static constexpr std::array<uint32_t, 6> kIndices = {0, 1, 3, 1, 2, 3};
};

struct Quad3D {
  static constexpr std::array<Vertex, 8> kData = {
      {{.pos = glm::vec3(-0.5f, -0.5f, 0.5f), .uv = glm::vec2(0.0f, 0.0f)},
       {.pos = glm::vec3(0.5f, -0.5f, 0.5f), .uv = glm::vec2(1.0f, 0.0f)},
       {.pos = glm::vec3(0.5f, 0.5f, 0.5f), .uv = glm::vec2(1.0f, 1.0f)},
       {.pos = glm::vec3(-0.5f, 0.5f, 0.5f), .uv = glm::vec2(0.0f, 1.0f)},
       {.pos = glm::vec3(-0.5f, -0.5f, -0.5f), .uv = glm::vec2(1.0f, 0.0f)},
       {.pos = glm::vec3(0.5f, -0.5f, -0.5f), .uv = glm::vec2(0.0f, 0.0f)},
       {.pos = glm::vec3(0.5f, 0.5f, -0.5f), .uv = glm::vec2(0.0f, 1.0f)},
       {.pos = glm::vec3(-0.5f, 0.5f, -0.5f), .uv = glm::vec2(1.0f, 1.0f)}}};

  static constexpr std::array<uint32_t, 36> kIndices = {
      0, 1, 2, 2, 3, 0,  // Front
      1, 5, 6, 6, 2, 1,  // Right
      5, 4, 7, 7, 6, 5,  // Back
      4, 0, 3, 3, 7, 4,  // Left
      3, 2, 6, 6, 7, 3,  // Top
      4, 5, 1, 1, 0, 4   // Bottom
  };
};

}  // namespace musashi

#endif
