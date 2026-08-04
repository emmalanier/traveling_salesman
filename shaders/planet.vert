#version 330 core

layout(location=0) in vec3 vert_position;
layout(location=1) in vec3 vert_normal;

out vec3 fragment_position;
out vec3 normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main()
{
    fragment_position = vec3(model*vec4(vert_position, 1.0))
    normal = mat3(transpose(inverse(model))) * vert_normal;
    gl_Position = projection * view * vec4(fragment_position, 1.0);
}