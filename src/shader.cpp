#include "shader.h"

#include <fstream>
#include <string>

Shader::Shader(const char *vertexPath, const char *fragmentPath) : ID(0) {
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

  unsigned int vertex, fragment;
  vertex = glCreateShader(GL_VERTEX_SHADER);
}
