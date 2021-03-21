#version 330 core
layout (location = 0) out vec4 diffuseColor;

struct Light
{
  vec2 position;
};

uniform Light light;

in data
{
	vec4 position;
	vec4 color;
} fragment_shader_in;

void main() {
    float intensity = 1.0 / length(fragment_shader_in.position.xy - light.position);
    diffuseColor = fragment_shader_in.color * intensity;
}