#version 330 core
out vec4 FragColor;

in vec3 LightDir;
in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

struct Light {
  vec3 position;
  vec3 color;
  float ambientStrength;
};

uniform Light light;

uniform vec3 viewPos;

float specularStrength = 0.5;

void main() {
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-LightDir, Normal);
  vec3 ambient = light.color * light.ambientStrength;
  vec3 diffuse = max(dot(LightDir, Normal), 0.0) * light.color;
  float spec =pow(max(dot(viewDir, reflectDir), 0.0), 32.0);  
  vec3 specular = specularStrength * spec * light.color * vec3(texture(texture_specular1, TexCoords));
  vec4 color = texture(texture_diffuse1, TexCoords);
  vec3 result = (ambient + diffuse + specular);
  FragColor = color * vec4(result, 1.0);
}
