// Copyright © 2024 Robert O'Shea

#include "oglengine/light.hpp"

Light::Light(glm::vec3 position, glm::vec3 color, float ambientStrength)
    : position(position), color(color), ambientStrength(ambientStrength) {}

void Light::ApplyToShader(const Shader &shader) const {
  shader.SetVec3f("light.position", position);
  shader.SetVec3f("light.color", color);
  shader.Set1f("light.ambientStrength", ambientStrength);
}
