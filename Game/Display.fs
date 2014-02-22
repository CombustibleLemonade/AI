#version 330 core

vec4 Color;
uniform sampler2D textureSampler;
in vec2 UV;

void main(void) {
	Color = texture2D(textureSampler, UV);
	gl_FragColor = vec4(Color);
}
