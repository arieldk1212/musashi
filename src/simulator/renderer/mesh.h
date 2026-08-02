#ifndef MESH_H_
#define MESH_H_

#include <array>

#include <glad/glad.h>
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

  template <size_t VerticesSize, size_t IndicesSize>
  void Init(const std::array<Vertex, VerticesSize>& vertices,
            const std::array<uint32_t, IndicesSize>& indices = {}) {
    vertices_count_ = static_cast<uint32_t>(vertices.size());
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ibo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    if (indices.size() > 0) {
      index_count_ = static_cast<uint32_t>(indices.size());
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                   indices.data(), GL_STATIC_DRAW);
    }

    SetupLayout();
  }

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

struct IMesh {
  virtual ~IMesh() = default;

  virtual void Init() = 0;
  virtual VertexData& GetVertex() = 0;
};

template <size_t VerticesSize, size_t IndicesSize>
struct Mesh : public IMesh {
  VertexData vertex;
  std::array<Vertex, VerticesSize> data;
  std::array<uint32_t, IndicesSize> indices;

  Mesh(const std::array<Vertex, VerticesSize>& data,
       const std::array<uint32_t, IndicesSize>& indices)
      : data(data),
        indices(indices) {
    Init();
  }

  void Init() override { vertex.Init(data, indices); }
  VertexData& GetVertex() override { return vertex; }
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
