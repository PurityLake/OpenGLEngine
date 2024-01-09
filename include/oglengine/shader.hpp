// Copyright © 2024 Robert O'Shea

#ifndef __HPP_SHADER__
#define __HPP_SHADER__

#include <glad/glad.h>

#include <optional>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define UNWRAP_SHADER(shaderName, shaderOpt, errorCode)                        \
  if (!((shaderOpt).has_value())) {                                            \
    errorCode;                                                                 \
  }                                                                            \
  (shaderName) = (shaderOpt).value();

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
  Shader(const Shader &other);
  Shader(Shader &&other);
  ~Shader();

  Shader &operator=(const Shader &other);
  Shader &operator=(Shader &&other);

  unsigned int GetID() const;

  bool IsValid() const;

  void Delete();
  void Use() const;

  void SetBool(const std::string &name, bool value) const;
  void SetBool(unsigned int location, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetInt(unsigned int location, int value) const;

  void SetMat4(const std::string &name, const glm::mat4 &mat) const;
  void SetMat4(unsigned int location, const glm::mat4 &mat) const;

  void Set1f(const std::string &name, float value) const;
  void Set1f(unsigned int location, float value) const;
  void Set2f(const std::string &name, float x, float y) const;
  void Set2f(unsigned int location, float x, float y) const;
  void Set3f(const std::string &name, float x, float y, float z) const;
  void Set3f(unsigned int location, float x, float y, float z) const;
  void Set4f(const std::string &name, float x, float y, float z, float w) const;
  void Set4f(unsigned int location, float x, float y, float z, float w) const;

  void SetVec1f(const std::string &name, const glm::vec1 &vec) const;
  void SetVec1f(unsigned int location, const glm::vec1 &vec) const;
  void SetVec2f(const std::string &name, const glm::vec2 &vec) const;
  void SetVec2f(unsigned int location, const glm::vec2 &vec) const;
  void SetVec3f(const std::string &name, const glm::vec3 &vec) const;
  void SetVec3f(unsigned int location, const glm::vec3 &vec) const;
  void SetVec4f(const std::string &name, const glm::vec4 &vec) const;
  void SetVec4f(unsigned int location, const glm::vec4 &vec) const;

private:
  unsigned int m_ID;
};

#endif // __HPP_SHADER__
