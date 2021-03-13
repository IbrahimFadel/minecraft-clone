#version 330 core

in vec2 UV;
in vec3 normal;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
	vec3 textureColor = texture( textureSampler, UV ).rgb;

    color.rgb = textureColor;
    color.a = 1.0;
}