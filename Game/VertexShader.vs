#version 330 core

attribute vec2 coord2d;
uniform float zoom = 0.5;

void main(void) {
	gl_Position = vec4(coord2d * zoom, 0.0, 1.0);
}
