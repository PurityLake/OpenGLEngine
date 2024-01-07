#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 LightDir;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

struct Light {
  vec3 position;
  vec3 color;
  float ambientStrength;
};

uniform Light light;

void main() {
  TexCoords = aTexCoords;
  Normal = mat3(transpose(inverse(model))) * aNormal;
  FragPos = vec3(model * vec4(aPos, 1.0));
  LightDir = normalize(FragPos - light.position);
  gl_Position = projection * view * model * vec4(aPos, 1.0);
}
