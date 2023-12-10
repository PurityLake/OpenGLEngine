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

vec3 lightPos = vec3(0.0, 5.0, -5.0);

void main() {
  TexCoords = aTexCoords;
  Normal = aNormal;
  FragPos = (model * vec4(aPos, 1.0)).xyz;
  LightDir = normalize(FragPos - lightPos);
  gl_Position = projection * view * model * vec4(aPos, 1.0);
}
