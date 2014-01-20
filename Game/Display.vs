#version 330 core

layout(location = 0) in vec2 coord2d;
layout(location = 1) in vec2 UVcoord;
layout(location = 2) in vec2 Fullscreencoord;
uniform float zoom = 200;
uniform int xRes = 1280;
uniform int yRes = 720;
uniform vec2 Position = vec2(0.0, 0.0);
uniform float FullscreenBlend;

out vec2 UV;

void main(void) {
	vec2 coord2dStorage;
	UV = vec2(UVcoord[0], UVcoord[1]);
	if (FullscreenBlend == 0.0) {
		coord2d[0] = (coord2d[0]+Position[0])/xRes;
		coord2d[1] = (coord2d[1]+Position[1])/yRes;
		gl_Position = vec4(coord2d*zoom, 0.0, 1.0);
	} else if (FullscreenBlend <1.0) {
		coord2dStorage[0] = UVcoord[0];
		coord2dStorage[1] = UVcoord[1];
		coord2d[0] = (coord2d[0]+Position[0])/xRes;
		coord2d[1] = (coord2d[1]+Position[1])/yRes;
		gl_Position = vec4(mix(coord2d*zoom, coord2dStorage, FullscreenBlend), 0.0, 1.0);
		
	}
	else if (FullscreenBlend >= 1.0) {
		gl_Position = vec4(coord2d , 0.0, 1.0);
	}
}
