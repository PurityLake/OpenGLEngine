#include "oglengine/shader.hpp"

#include <iostream>

Shader::Shader() : m_ID(0) {}
Shader::Shader(unsigned int programID) : m_ID(programID) {}
Shader::Shader(const Shader &other) : m_ID(other.m_ID) {}
Shader::Shader(Shader &&other) : m_ID(other.m_ID) { other.m_ID = 0; }

Shader::~Shader() {}

Shader &Shader::operator=(const Shader &other) {
  m_ID = other.m_ID;
  return *this;
}
Shader &Shader::operator=(Shader &&other) {
  m_ID = other.m_ID;
  other.m_ID = 0;
  return *this;
}

unsigned int Shader::GetID() const { return m_ID; }

bool Shader::IsValid() const { return m_ID != 0 && glIsProgram(m_ID); }

void Shader::Delete() {
  if (IsValid()) {
    glDeleteProgram(m_ID);
    m_ID = 0;
  }
}

void Shader::Use() const { glUseProgram(m_ID); }

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

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(mat));
}
void Shader::SetMat4(unsigned int location, const glm::mat4 &mat) const {
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::Set1f(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::Set1f(unsigned int location, float value) const {
  glUniform1f(location, value);
}

void Shader::Set2f(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
}
void Shader::Set2f(unsigned int location, float x, float y) const {
  glUniform2f(location, x, y);
}
void Shader::Set3f(const std::string &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
}
void Shader::Set3f(unsigned int location, float x, float y, float z) const {
  glUniform3f(location, x, y, z);
}
void Shader::Set4f(const std::string &name, float x, float y, float z,
                   float w) const {
  glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
}
void Shader::Set4f(unsigned int location, float x, float y, float z,
                   float w) const {
  glUniform4f(location, x, y, z, w);
}

void Shader::SetVec1f(const std::string &name, const glm::vec1 &vec) const {
  glUniform1fv(glGetUniformLocation(m_ID, name.c_str()), vec.length(),
               glm::value_ptr(vec));
}
void Shader::SetVec1f(unsigned int location, const glm::vec1 &vec) const {
  glUniform1fv(location, vec.length(), glm::value_ptr(vec));
}
void Shader::SetVec2f(const std::string &name, const glm::vec2 &vec) const {
  glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), vec.length(),
               glm::value_ptr(vec));
}
void Shader::SetVec2f(unsigned int location, const glm::vec2 &vec) const {
  glUniform2fv(location, vec.length(), glm::value_ptr(vec));
}
void Shader::SetVec3f(const std::string &name, const glm::vec3 &vec) const {
  glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), vec.length(),
               glm::value_ptr(vec));
}
void Shader::SetVec3f(unsigned int location, const glm::vec3 &vec) const {
  glUniform3fv(location, vec.length(), glm::value_ptr(vec));
}
void Shader::SetVec4f(const std::string &name, const glm::vec4 &vec) const {
  glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), vec.length(),
               glm::value_ptr(vec));
}
void Shader::SetVec4f(unsigned int location, const glm::vec4 &vec) const {
  glUniform4fv(location, vec.length(), glm::value_ptr(vec));
}
