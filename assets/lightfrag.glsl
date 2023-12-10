#version 330 core
out vec4 FragColor;

in vec3 LightDir;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main() {
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;
  vec3 diffuse = max(dot(LightDir, Normal), 0.0) * lightColor;
  vec4 color = texture(texture_diffuse1, TexCoords);
  vec3 result = (ambient + diffuse);
  FragColor = color * vec4(result, 1.0);
}
