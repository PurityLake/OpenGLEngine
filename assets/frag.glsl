#version 400 core
out vec4 FragColor;

in vec3 outColor;

void main() { FragColor = vec4(outColor + vec3(0.5f), 1.0f); }
