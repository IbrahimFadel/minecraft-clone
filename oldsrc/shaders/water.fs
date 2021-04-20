#version 330 core

in vec2 UV;
in vec3 normal;
in vec3 position;

out vec4 color;

uniform sampler2D textureSampler;
uniform sampler2D reflectionTextureSampler;
uniform vec3 cameraPos;

void main() {
    vec3 texColor = texture(textureSampler, UV).rgb;
    color.rgb = texColor;
    color.a = 0.4;
}