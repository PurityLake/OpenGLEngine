// Copyright © 2024 Robert O'Shea

#ifndef __HPP_LIGHT__
#define __HPP_LIGHT__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "oglengine/shader.hpp"

struct Light {
  glm::vec3 position;
  glm::vec3 color;
  float ambientStrength;

  Light(glm::vec3 position, glm::vec3 color, float ambientStrength);
  Light(const Light &other);

  void ApplyToShader(const Shader &shaer) const;
};

#endif // __HPP_LIGHT__
