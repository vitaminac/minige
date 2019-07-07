#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_position;

in data
{
	vec4 position;
	vec4 color;
} fragment_shader_in;

void main() {
    float intensity = 1.0 / length(fragment_shader_in.position.xy - light_position);
    color = fragment_shader_in.color * intensity;
}