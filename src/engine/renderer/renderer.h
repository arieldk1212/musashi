#ifndef RENDERER_H_
#define RENDERER_H_

#include <filesystem>

namespace musashi {

class Renderer {
 public:
  using ShaderID = uint16_t;

  Renderer();

  ShaderID CreateGraphicsShader(const std::filesystem::path& vertex_shader,
                                const std::filesystem::path& fragment_shader);
  void LoadTexture();
};

}  // namespace musashi

#endif