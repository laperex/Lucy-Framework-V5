#version 450 core

in vec3 normal;
in vec4 color;
in float textureid;
in float idx;

in vec2 uv0;
in vec2 uv1;
in vec2 uv2;
in vec2 uv3;
in vec2 uv4;
in vec2 uv5;
in vec2 uv6;
in vec2 uv7;

layout(binding = 0) uniform sampler2DArray u_texturearray;

vec4 GetColor() {
	return texture(u_texturearray, vec3(uv0, idx));
}

void main() {
	gl_FragColor = GetColor();
}