#ifndef __HPP_RENDER__
#define __HPP_RENDER__

#include <oglengine/model.hpp>

#include <vector>

class Renderer {
public:
  Renderer() = default;
  ~Renderer() = default;

  void Draw(const std::vector<Model> &models, glm::mat4 &view,
            glm::mat4 &projection) const {

    auto modelMat =
        glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
                   glm::vec3(1.0f, 1.0f, 1.0f));
    for (const auto &model : models) {
      for (const auto &mesh : model.m_Meshes) {
        model.shader.Use();
        model.shader.SetMat4("model", modelMat);
        model.shader.SetMat4("view", view);
        model.shader.SetMat4("projection", projection);

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        for (int i = 0; i < mesh.m_Textures.size(); ++i) {
          glActiveTexture(GL_TEXTURE0 + i);
          unsigned int id = mesh.m_Textures[i].ID;
          std::string number;
          std::string name;
          glBindTexture(GL_TEXTURE_2D, id);
          if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
          } else if (name == "texture_specular") {
            number = std::to_string(specularNr++);
          } else if (name == "texture_normal") {
            number = std::to_string(normalNr++);
          } else if (name == "texture_height") {
            number = std::to_string(heightNr++);
          }
          model.shader.SetInt((name + number).c_str(), i);
        }
        glBindVertexArray(mesh.m_VAO);
        glDrawElements(GL_TRIANGLES, mesh.m_Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
      }
    }
  }
};

#endif // __HPP_RENDER__
