#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>

#include <string>

class Shader {
public:
  Shader(const char *vertexPath, const char *fragmentPath);

  unsigned int GetID() const;

  bool IsValid() const;

  void Use() const;

  void SetBool(const std::string &name, bool value) const;
  void SetBool(unsigned int location, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetInt(unsigned int location, int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetFloat(unsigned int location, float value) const;
  
  void SetVec4f(const std::string &name, float x, float y, float z, float w) const;
  void SetVec4f(unsigned int location, float x, float y, float z, float w) const;

private:
  unsigned int m_ID;
  bool m_Valid;
};

#endif
