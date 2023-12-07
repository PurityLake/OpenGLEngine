#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

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

Shader::Shader(const char *vertexPath, const char *fragmentPath) : m_ID(0), m_Valid(true) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cout << "ERROR:SHADER::FILE_NOT_SUCCESSFULL_READ" << std::endl;
  }

  const char *vCode = vertexCode.c_str();
  const char *fCode = fragmentCode.c_str();

  unsigned int vertex, fragment;
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vCode, nullptr);
  glCompileShader(vertex);
  if (!checkShaderCompileStatus(vertex)) {
    m_Valid = false;
    goto vert_error;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fCode, nullptr);
  glCompileShader(fragment);
  if (!checkShaderCompileStatus(fragment)) {
    m_Valid = false;
    goto frag_error;
  }

  m_ID = glCreateProgram();
  glAttachShader(m_ID, vertex);
  glAttachShader(m_ID, fragment);
  glLinkProgram(m_ID);
  if (!checkShaderLinkStatus(m_ID)) {
    m_Valid = false;
    goto link_error;
  }

  return;

link_error:
  glDeleteProgram(m_ID);

frag_error:
  glDeleteShader(fragment);

vert_error:
  glDeleteShader(vertex);
}

unsigned int Shader::GetID() const {
  return m_ID;
}

bool Shader::IsValid() const {
  return m_Valid;
}

void Shader::Use() const {
  glUseProgram(m_ID);
}

void Shader::SetBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}
void Shader::SetBool(unsigned int location, bool value) const {
  glUniform1i(location, (int)value);
}
void Shader::SetInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::SetInt(unsigned int location, int value) const {
  glUniform1i(location, value);
}
void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::SetFloat(unsigned int location, float value) const {
  glUniform1f(location, value);
}

