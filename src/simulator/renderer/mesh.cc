#include "mesh.h"

namespace musashi {

VertexData::~VertexData() {
  Destroy();
}

void VertexData::Bind() const {
  glBindVertexArray(vao_);
}

void VertexData::Draw() const {
  if (index_count_ > 0) {
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
    return;
  }

  if (vertices_count_ > 0) {
    glDrawArrays(GL_TRIANGLES, 0, vertices_count_);
    return;
  }
}

void VertexData::Destroy() {
  glDeleteVertexArrays(1, &vao_);
  glDeleteBuffers(1, &vbo_);
  glDeleteBuffers(1, &ibo_);
  vao_ = vbo_ = ibo_ = 0;
}

void VertexData::Unbind() {
  glBindVertexArray(0);
}

void VertexData::SetupLayout() {
  auto stride = sizeof(Vertex);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride,
                        (void*)offsetof(Vertex, pos));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride,
                        (void*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

}  // namespace musashi
