#version 330 core
out vec4 FragColor;

in vec3 LightDir;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

struct Light {
  vec3 position;
  vec3 color;
  float ambientStrength;
};

uniform Light light;

void main() {
  vec3 ambient = light.color * light.ambientStrength;
  vec3 diffuse = max(dot(LightDir, Normal), 0.0) * light.color;
  vec4 color = texture(texture_diffuse1, TexCoords);
  vec3 result = (ambient + diffuse);
  FragColor = color * vec4(result, 1.0);
}
