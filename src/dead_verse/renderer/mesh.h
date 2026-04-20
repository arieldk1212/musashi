#ifndef MESH_H_
#define MESH_H_

#include <vector>

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

  void Init(const std::vector<Vertex>& vertices,
            const std::vector<uint32_t>& indices = {});

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
  std::vector<Vertex> data;
  std::vector<uint32_t> indices;

  Mesh(const std::vector<Vertex>& data, const std::vector<uint32_t>& indices)
      : data(data),
        indices(indices) {
    vertex.Init(data, indices);
  }
};

struct Quad2D {
  inline static std::vector<Vertex> data = {
      {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
      {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
      {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
      {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}}};

  inline static std::vector<uint32_t> indices = {0, 1, 3, 1, 2, 3};
};

struct Quad3D {
  inline static std::vector<Vertex> data = {
      // NOTE: Without UVs
      // {{-0.5f, -0.5f, 0.5f}}, {{0.5f, -0.5f, 0.5f}},   {{0.5f, 0.5f, 0.5f}},
      // {{-0.5f, 0.5f, 0.5f}},  {{-0.5f, -0.5f, -0.5f}}, {{0.5f, -0.5f,
      // -0.5f}},
      // {{0.5f, 0.5f, -0.5f}},  {{-0.5f, 0.5f, -0.5f}}};

      {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
      {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
      {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},
      {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
      {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
      {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},
      {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}}};
  inline static std::vector<uint32_t> indices = {
      0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 5, 4, 7, 7, 6, 5,
      4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 4, 5, 1, 1, 0, 4};
};

}  // namespace musashi

#endif
