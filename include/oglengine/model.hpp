#ifndef __HPP_MESH__
#define __HPP_MESH__

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  unsigned int ID;
  std::string Type;
};

struct Mesh {
public:
  std::vector<Vertex> m_Vertices;
  std::vector<unsigned int> m_Indices;
  std::vector<Texture> m_Textures;

  Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned int> &&indices,
       std::vector<Texture> &&textures);

private:
  unsigned int m_VAO, m_VBO, m_EBO;

  void Setup();
};

#endif // __HPP_MESH__
