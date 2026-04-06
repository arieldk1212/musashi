#ifndef RENDERER_H_
#define RENDERER_H_

#include <string>
#include <unordered_map>

#include "platform/glfw/frame_buffer.h"
#include "renderer/texture.h"

namespace musashi {

class Renderer {
 public:
  Renderer() = default;

  void Tick();
  void Render();
  void Update();

 private:
  // TODO: add a umap of textures, frame buffers, programs, uniforms.
  // TODO: prob vector of manages resources, ptr to sprite renderer, particle.
  std::unordered_map<std::string, Texture> textures_;
  std::unordered_map<std::string, FrameBuffer> frame_buffers_;
};

}  // namespace musashi

#endif
