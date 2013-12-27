#version 330 core

attribute vec2 coord2d;
uniform float zoom = 500;
uniform int xRes = 1600;
uniform int yRes = 900;
uniform vec2 Position;

void main(void) {
	coord2d[0] = coord2d[0]/xRes;
	coord2d[1] = coord2d[1]/yRes;
	gl_Position = vec4(coord2d*zoom, 0.0, 1.0);
}
