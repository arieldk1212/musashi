#ifndef SHADER_H_
#define SHADER_H_

#include <filesystem>
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Musashi {

class Shader {
public:
  // constructor reads and builds the shader
  Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath);

  // the program ID
  uint16_t ID;

  // use/activate the shader
  void use();
  void delete_program();
  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
  void checkCompileErrors(uint16_t shader, const std::string &type) const {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout
            << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
            << infoLog
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
      }
    } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout
            << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
            << infoLog
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
      }
    }
  }
};

} // namespace Musashi

#endif