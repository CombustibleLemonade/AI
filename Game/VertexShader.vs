#version 330 core

attribute vec2 coord2d;
uniform float zoom = 500;
uniform int xRes = 1280;
uniform int yRes = 720;
uniform vec2 Position = vec2(0.0, 0.0);

void main(void) {
	coord2d[0] = (coord2d[0]+Position[0])/xRes;
	coord2d[1] = (coord2d[1]+Position[1])/yRes;
	gl_Position = vec4(coord2d*zoom, 0.0, 1.0);
}
