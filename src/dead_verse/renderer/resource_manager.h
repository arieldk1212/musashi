#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "renderer/shader.h"
#include "renderer/texture.h"
namespace musashi {

class ResourceManager {
 public:
  using Program = Shader;
  using ProgramName = ShaderName;

  void InitResources();

  void AddProgram();
  void UseProgram();

  Program& GetProgram(ProgramName name) { return *programs_[name]; }
  template <typename T>
  T& Get(T resource);

 private:
  std::unordered_map<TextureId, std::shared_ptr<Texture>> textures_;
  std::unordered_map<ProgramName, std::unique_ptr<Program>> programs_;
};

}  // namespace musashi

#endif
