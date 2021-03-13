#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

out vec2 UV;
out vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    normal = mat3(transpose(inverse(model))) * aNormal;

    UV = aUV;

    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(aPos, 1.0);
}