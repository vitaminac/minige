#version 330 core
layout (location = 0) out vec4 diffuseColor;
layout (location = 1) out int materialID;
layout (location = 2) out vec4 specularColor;
layout (location = 3) out vec3 position;
layout (location = 4) out vec3 normal;

struct Light
{
  vec2 position;
};

uniform Light light;
uniform sampler2D tex;

in data
{
	vec4 position;
	vec4 color;
} fragment_shader_in;

void main() {
    float intensity = 1.0 / length(fragment_shader_in.position.xy - light.position);
    diffuseColor = fragment_shader_in.color * intensity + texture2D(tex, fragment_shader_in.position.xy);
}