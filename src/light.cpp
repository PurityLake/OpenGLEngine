#include "oglengine/light.hpp"

Light::Light(glm::vec3 position, glm::vec3 color, float ambientStrength)
    : position(position), color(color), ambientStrength(ambientStrength) {}

void Light::ApplyToShader(const Shader &shader) const {
  shader.SetVec4f("Light.position", glm::vec4(position, 1.0f));
  shader.SetVec3f("Light.color", color);
  shader.Set1f("Light.ambientStrength", ambientStrength);
}
