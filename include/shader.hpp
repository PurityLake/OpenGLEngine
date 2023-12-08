#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <glad/glad.h>

#include <optional>
#include <string>
#include <vector>

#define UNWRAP_SHADER(shaderName, shaderOpt, errorCode)                        \
  if (!((shaderOpt).has_value())) {                                            \
    errorCode;                                                                 \
  }                                                                            \
  shader = (shaderOpt).value();

class Shader;

class ShaderBuilder {
public:
  ShaderBuilder();

  ShaderBuilder &AddShader(GLenum type, const char *path);
  ShaderBuilder &AddShader(GLenum type, std::string &path);

  std::optional<Shader> Build();

  void Clear();

private:
  struct ShaderEntry {
    GLenum type;
    std::string path;
  };
  std::vector<ShaderEntry> m_ShaderEntries;
};

class Shader {
public:
  Shader();
  Shader(unsigned int programID);

  unsigned int GetID() const;

  void Use() const;

  void SetBool(const std::string &name, bool value) const;
  void SetBool(unsigned int location, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetInt(unsigned int location, int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetFloat(unsigned int location, float value) const;

  void SetVec4f(const std::string &name, float x, float y, float z,
                float w) const;
  void SetVec4f(unsigned int location, float x, float y, float z,
                float w) const;

private:
  unsigned int m_ID;
};

#endif // __SHADER_HPP__
