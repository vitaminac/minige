#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 projection_matrix;
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out data {
    vec4 position;
    vec4 color;
} vertex_shader_out;

void main() {
    gl_Position = projection_matrix * view_matrix * model_matrix * position;
    vertex_shader_out.position = model_matrix * position;
    vertex_shader_out.color = color;
}