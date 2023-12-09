#ifndef __HPP_MESH__
#define __HPP_MESH__

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "oglengine/shader.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  unsigned int ID;
  std::string Type;
  std::string Path;
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

struct Model {
public:
  std::vector<Mesh> m_Meshes;
  Shader shader;

  Model(const char *path, Shader &shader);

private:
  std::vector<Texture> m_LoadedTextures;
  std::string m_Directory;

  void LoadModel(const std::string &path);
  void ProcessModel(aiNode *node, const aiScene *scene);
  Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            std::string typeName);
};

#endif // __HPP_MESH__
