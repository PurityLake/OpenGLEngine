#include "oglengine/model.hpp"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <oglengine/stb_image.h>

#include <iostream>

unsigned int TextureFromFile(const char *path, const std::string &directory,
                             bool gamma) {
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data =
      stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1) {
      format = GL_RED;
    } else if (nrComponents == 3) {
      format = GL_RGB;
    } else if (nrComponents == 4) {
      format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

Model::Model(const char *path, Shader &shader) : shader(shader) {
  LoadModel(path);
}

void Model::LoadModel(const std::string &path) {

  Assimp::Importer importer;
  const aiScene *scene =
      importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene | scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
  }
  m_Directory = path.substr(0, path.find_last_of('/'));

  ProcessModel(scene->mRootNode, scene);
}

void Model::ProcessModel(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    m_Meshes.push_back(ProcessMesh(mesh, scene));
  }
  for (unsigned int i = 0; i < node->mNumChildren; ++i) {
    ProcessModel(node->mChildren[i], scene);
  }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex;

    vertex.Position = glm::vec3{mesh->mVertices[i].x, mesh->mVertices[i].y,
                                mesh->mVertices[i].z};

    vertex.Normal = glm::vec3{mesh->mNormals[i].x, mesh->mNormals[i].y,
                              mesh->mNormals[i].z};

    if (mesh->mTextureCoords[0]) {
      vertex.TexCoords =
          glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
    } else {
      vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; ++j) {
      indices.push_back(face.mIndices[j]);
    }
  }

  if (mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = LoadMaterialTextures(
        material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = LoadMaterialTextures(
        material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps =
        LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps =
        LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
  }

  return Mesh(std::move(vertices), std::move(indices), std::move(textures));
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *mat,
                                                 aiTextureType type,
                                                 std::string typeName) {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
    aiString str;
    bool skip = false;

    mat->GetTexture(type, i, &str);
    for (unsigned int j = 0; j < m_LoadedTextures.size(); ++j) {
      if (std::strcmp(m_LoadedTextures[j].Path.data(), str.C_Str()) == 0) {
        textures.push_back(m_LoadedTextures[j]);
        skip = true;
        break;
      }
    }
    if (!skip) {
      Texture texture;
      texture.ID = TextureFromFile(str.C_Str(), m_Directory, false);
      texture.Type = typeName;
      texture.Path = str.C_Str();
      textures.push_back(texture);
      m_LoadedTextures.push_back(texture);
    }
  }
  return textures;
}
