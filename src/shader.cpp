#include "shader.hpp"

Shader::Shader() : m_ID(-1) {}
Shader::Shader(unsigned int programID) : m_ID(programID) {}

unsigned int Shader::GetID() const { return m_ID; }

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
void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::SetFloat(unsigned int location, float value) const {
  glUniform1f(location, value);
}

void Shader::SetVec4f(const std::string &name, float x, float y, float z,
                      float w) const {
  glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
}
void Shader::SetVec4f(unsigned int location, float x, float y, float z,
                      float w) const {
  glUniform4f(location, x, y, z, w);
}
