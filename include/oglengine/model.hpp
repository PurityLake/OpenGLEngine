#ifndef __HPP_MODEL__
#define __HPP_MODEL__

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
  glm::mat4 m_Tranform;

  Mesh(std::vector<Vertex> &&vertices, std::vector<unsigned int> &&indices,
       std::vector<Texture> &&textures, glm::mat4 &trans);

  unsigned int m_VAO, m_VBO, m_EBO;

private:
  void Setup();
};

struct Model {
public:
  std::vector<Mesh> m_Meshes;
  Shader m_Shader;

  Model(const char *path, Shader &shader);
  Model(const Model &other);
  Model(Model &&other);
  ~Model();

private:
  std::vector<Texture> m_LoadedTextures;
  std::string m_Directory;

  void LoadModel(const std::string &path);
  void ProcessModel(aiNode *node, const aiScene *scene);
  void ProcessModel(aiNode *node, const aiScene *scene, glm::mat4 &trans);
  Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene, glm::mat4 &trans);
  std::vector<Texture> LoadMaterialTextures(const aiScene *scene,
                                            aiMaterial *mat, aiTextureType type,
                                            std::string typeName);
};

#endif // __HPP_MODEL__
