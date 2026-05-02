#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <filesystem>
#include <memory>
#include <unordered_map>

#include "renderer/shader.h"
#include "renderer/texture.h"
#include "util/log.h"

namespace musashi {

class ResourceManager {
 public:
  explicit ResourceManager(Logger& logger)
      : logger_(&logger) {}

  enum class ShaderName : uint8_t { kObjectShader };
  enum class TextureName : uint8_t {
    kZombiesSheet,
  };

  using Program = Shader;
  using ProgramName = ShaderName;

  void InitResources() {
    AddProgram(ResourceManager::ShaderName::kObjectShader,
               "assets/shaders/object/vert.glsl",
               "assets/shaders/object/frag.glsl");
    UseProgram(ResourceManager::ShaderName::kObjectShader);
    AddTexture(TextureName::kZombiesSheet,
               "assets/sprites/zombies/sprite_sheet.png");
  }
  void ClearResources() {
    textures_.clear();
    programs_.clear();
    logger_->Trace("RESOURCES DELETED");
  }

  void AddProgram(ShaderName name, const std::filesystem::path& vertex_path,
                  const std::filesystem::path& fragment_path) {
    programs_[name] = std::make_unique<Program>(vertex_path, fragment_path);
    logger_->Trace("PROGRAM ADDED");
  }
  void UseProgram(ProgramName name) { programs_[name]->Use(); }
  Program& GetProgram(ProgramName name) { return *programs_[name]; }
  void DeleteProgram(ProgramName name) {
    programs_.erase(name);
    logger_->Trace("PROGRAM DELETED");
  }

  void AddTexture(TextureName name, const std::filesystem::path& path) {
    textures_[name] = std::make_shared<Texture>(path);
    logger_->Trace("TEXTURE ADDED");
  }
  std::shared_ptr<Texture> GetTexture(TextureName name) {
    return textures_[name];
  }
  void DeleteTexture(TextureName name) {
    textures_.erase(name);
    logger_->Trace("TEXTURE DELETED");
  }

 private:
  Logger* logger_;
  std::unordered_map<TextureName, std::shared_ptr<Texture>> textures_;
  std::unordered_map<ProgramName, std::unique_ptr<Program>> programs_;
};

}  // namespace musashi

#endif
