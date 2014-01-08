#version 330 core

vec4 Color;

in vec2 UV;
uniform sampler2D textureSampler;

void main(void) {
	Color = texture2D(textureSampler, UV);
	gl_FragColor = vec4(Color);
}
