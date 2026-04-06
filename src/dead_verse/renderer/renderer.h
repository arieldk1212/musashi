#ifndef RENDERER_H_
#define RENDERER_H_

#include <filesystem>

namespace musashi {

class Renderer {
 public:
  using ShaderID = uint16_t;

  Renderer() = default;

  void Render();
  void Update();
  void LoadTexture();
  ShaderID CreateGraphicsShader(const std::filesystem::path& vertex_shader,
                                const std::filesystem::path& fragment_shader);

 private:
  // TODO: add a umap of textures, frame buffers, programs, uniforms.
  // TODO: prob vector of manages resources, ptr to sprite renderer, particle.
};

}  // namespace musashi

#endif
