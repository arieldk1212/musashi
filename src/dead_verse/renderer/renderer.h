#ifndef RENDERER_H_
#define RENDERER_H_

#include "shader.h"
#include "texture.h"

#include <string>
#include <unordered_map>

#include "platform/opengl/vertex_buffer.h"

namespace musashi {

class Renderer {
 public:
  Renderer() = default;

  void Tick();
  void Render(float ts);
  void Update();
  void ShutDown();

  void AddShader(std::string shader_name,
                 const std::filesystem::path& vertex_path,
                 const std::filesystem::path& fragment_path);

 private:
  // TODO: add a umap of textures, frame buffers, programs, uniforms.
  // TODO: prob vector of manages resources, ptr to sprite renderer, particle.
  std::unordered_map<std::string, Texture> textures_;
  // std::unordered_map<std::string, FrameBuffer> frame_buffers_;
  std::unordered_map<std::string, VertexBuffer> vertex_buffers_;
  std::unordered_map<std::string, std::unique_ptr<Shader>> shaders_;
};

}  // namespace musashi

#endif
