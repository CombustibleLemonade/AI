#version 330 core

layout(location = 0) in vec2 coord2d;
layout(location = 2) in vec2 UVcoord;
layout(location = 1) in vec2 Fullscreencoord;

uniform vec2 Scale = vec2(1, 1);
uniform float Zoom = 200;
uniform int xRes = 1280;
uniform int yRes = 720;
uniform vec2 Position = vec2(0.0, 0.0);
uniform float Rotation = 0.0;

out vec2 UV;

void main(void) {
	vec2 coord2dStorage;
	UV = vec2(UVcoord[0], UVcoord[1]);


	float X = coord2d[0];
	float Y = coord2d[1];
	coord2d[0] = X * cos(Rotation) - Y * sin(Rotation);
	coord2d[1] = X * sin(Rotation) + Y * cos(Rotation);

	coord2d[0] = (coord2d[0]*Scale[0]+Position[0])/xRes;
	coord2d[1] = (coord2d[1]*Scale[1]+Position[1])/yRes;
	gl_Position = vec4(coord2d*Zoom, 0.0, 1.0);
}
