#ifndef VERTEX_H_
#define VERTEX_H_

#include <array>
#include <vector>

#include <glad/glad.h>

namespace musashi {

struct Vertex {
  std::array<float, 3> pos;
  std::array<float, 3> normal;
  std::array<float, 3> uv;
  std::array<float, 2> color;
  std::array<float, 2> texture;
};

struct VertexBuffer {
  uint32_t vao;
  uint32_t vbo;

  void Init(const std::vector<Vertex>& data) {
    glGenBuffers(1, &vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(),
                 GL_STATIC_DRAW);
    glad_glGenVertexArrays(1, &vao);
    SetupVertexAttributes();
  }
  void Bind() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
  }
  void Destroy() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
  }

  static void Unbind() { glBindVertexArray(0); }
  static void SetupVertexAttributes(bool use_colors, bool use_uvs) {
    auto stride = sizeof(Vertex);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride,
                          (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                          (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride,
                          (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride,
                          (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, stride,
                          (void*)offsetof(Vertex, texture));
    glEnableVertexAttribArray(4);
  }
};

}  // namespace musashi

#endif
