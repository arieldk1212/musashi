#include "shader.h"

#include <array>
#include <fstream>
#include <print>
#include <sstream>

namespace musashi {

Shader::Shader(const std::filesystem::path& vertex_path,
               const std::filesystem::path& fragment_path) {
  std::string vertex_code;
  std::string fragment_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;

  // ensure ifstream objects can throw exceptions:
  v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    v_shader_file.open(vertex_path);
    f_shader_file.open(fragment_path);

    std::stringstream v_shader_stream;
    std::stringstream f_shader_stream;
    v_shader_stream << v_shader_file.rdbuf();
    f_shader_stream << f_shader_file.rdbuf();

    v_shader_file.close();
    f_shader_file.close();

    vertex_code = v_shader_stream.str();
    fragment_code = f_shader_stream.str();

  } catch (const std::ifstream::failure& e) {
    std::println("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
  }
  const char* vShaderCode = vertex_code.c_str();
  const char* fShaderCode = fragment_code.c_str();

  // compile shaders
  int success{0};
  unsigned int vertex{0};
  unsigned int fragment{0};
  std::array<char, 512> info_log{};

  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);

  // print error for vertex
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, nullptr, info_log.data());
    std::println("ERROR::SHADER::VERTEX::COMPILATION_FAILED: {}", info_log);
  };

  // fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);

  // print error for fragment
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, nullptr, info_log.data());
    std::println("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: {}", info_log);
  };

  // shader Program
  id_ = glCreateProgram();
  glAttachShader(id_, vertex);
  glAttachShader(id_, fragment);
  glLinkProgram(id_);
  // print linking errors if any
  glGetProgramiv(id_, GL_LINK_STATUS, &success);
  if (success == 0) {
    glGetProgramInfoLog(id_, 512, nullptr, info_log.data());
    std::println("ERROR::SHADER::PROGRAM::LINKING_FAILED: {}", info_log);
  }

  // delete the shaders as they're linked into our program now and no longer
  // necessary! IMPORTANT!
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::Use() const {
  glUseProgram(id_);
}

void Shader::DeleteProgram() const {
  glDeleteProgram(id_);
}

void Shader::SetBool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(id_, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& vec) const {
  glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, &vec[0]);
}

void Shader::CheckCompileErrors(uint16_t shader, const std::string& type) {
  int success = 0;
  std::array<char, 1024> info_log{};
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, info_log.data());
      std::println("ERROR::SHADER_COMPILATION_ERROR of type: {}\n{}", type,
                   info_log.data());
      std::println(
          "-- --------------------------------------------------- -- ");
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, info_log.data());
      std::println("ERROR::PROGRAM_LINKING_ERROR of type: {}\n{}", type,
                   info_log.data());
      std::println(
          "-- --------------------------------------------------- -- ");
    }
  }
}

}  // namespace musashi
