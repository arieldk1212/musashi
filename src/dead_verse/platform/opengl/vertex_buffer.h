#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace musashi {

struct Vertex {
  glm::vec3 pos;
  // glm::vec3 normal;
  // glm::vec2 uv;
};

class VertexBuffer {
 public:
  VertexBuffer() = default;
  ~VertexBuffer();

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

}  // namespace musashi

#endif
