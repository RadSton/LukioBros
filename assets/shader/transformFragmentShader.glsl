#version 330 core

out vec4 color;

in vec2 txCoords;

uniform sampler2D u_tex;

void main() {
	color = texture(u_tex,txCoords);
}