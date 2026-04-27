#ifndef SHADER_H_
#define SHADER_H_

#include <filesystem>
#include <string>

#include <glm/mat4x4.hpp>

namespace musashi {

enum class ShaderName : uint8_t { kObjectShader };

class Shader {
 public:
  Shader(const std::filesystem::path& vertex_path,
         const std::filesystem::path& fragment_path);
  ~Shader() { DeleteProgram(); }

  void Use() const;
  void DeleteProgram() const;

  void SetBool(const std::string& name, bool value) const;
  void SetInt(const std::string& name, int value) const;
  void SetFloat(const std::string& name, float value) const;
  void SetMat4(const std::string& name, const glm::mat4& mat) const;
  void SetVec3(const std::string& name, const glm::vec3& vec) const;
  void SetVec2(const std::string& name, const glm::vec2& vec) const;

 private:
  static void CheckCompileErrors(uint16_t shader, const std::string& type);

  uint8_t id_;
};

}  // namespace musashi

#endif
