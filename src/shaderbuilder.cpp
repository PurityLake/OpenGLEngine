// Copyright © 2024 Robert O'Shea

#include "oglengine/shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

static inline int checkShaderCompileStatus(unsigned int shader) {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  return success;
}

static inline int checkShaderLinkStatus(unsigned int program) {
  int success;
  char infoLog[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
  }
  return success;
}

ShaderBuilder::ShaderBuilder() : m_ShaderEntries() {}

ShaderBuilder &ShaderBuilder::AddShader(GLenum type, const char *path) {
  m_ShaderEntries.push_back({type, std::string(path)});
  return *this;
}
ShaderBuilder &ShaderBuilder::AddShader(GLenum type, std::string &path) {
  m_ShaderEntries.push_back({type, path});
  return *this;
}

std::optional<Shader> ShaderBuilder::Build() {
  std::vector<unsigned int> shaders;
  std::string shaderCode;
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  for (const ShaderEntry &entry : m_ShaderEntries) {
    try {
      std::stringstream stream;
      file.open(entry.path);
      stream << file.rdbuf();
      file.close();
      shaderCode = stream.str();
    } catch (std::ifstream::failure e) {
      std::cout << "ERROR:SHADER::FILE_NOT_SUCCESSFULL_READ" << std::endl;
      return std::nullopt;
    }
    const char *code = shaderCode.c_str();
    unsigned int shader = glCreateShader(entry.type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    if (!checkShaderCompileStatus(shader)) {
      return std::nullopt;
    }
    shaders.push_back(shader);
  }

  unsigned int id = glCreateProgram();
  for (unsigned int shader : shaders) {
    glAttachShader(id, shader);
  }
  glLinkProgram(id);
  if (!checkShaderLinkStatus(id)) {
    return std::nullopt;
  }

  for (unsigned int shader : shaders) {
    glDeleteShader(shader);
  }

  return std::optional<Shader>(Shader(id));
}

void ShaderBuilder::Clear() { m_ShaderEntries.clear(); }
