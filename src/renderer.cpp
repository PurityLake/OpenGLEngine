#include "oglengine/renderer.hpp"

void Renderer::Draw(const std::vector<Model> &models, glm::mat4 &view,
                    glm::mat4 &projection, const Light &light) const {
  for (const auto &model : models) {
    for (const auto &mesh : model.m_Meshes) {
      model.m_Shader.Use();
      model.m_Shader.SetMat4("model", mesh.m_Tranform);
      model.m_Shader.SetMat4("view", view);
      model.m_Shader.SetMat4("projection", projection);

      unsigned int diffuseNr = 1;
      unsigned int specularNr = 1;
      unsigned int normalNr = 1;
      unsigned int heightNr = 1;

      for (int i = 0; i < mesh.m_Textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        unsigned int id = mesh.m_Textures[i].ID;
        std::string number;
        std::string name = mesh.m_Textures[i].Type;
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
        model.m_Shader.SetInt((name + number).c_str(), i);
      }
      light.ApplyToShader(model.m_Shader);
      glBindVertexArray(mesh.m_VAO);
      glDrawElements(GL_TRIANGLES, mesh.m_Indices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

      glActiveTexture(GL_TEXTURE0);
    }
  }
}
