#version 330 core

uniform float X = -1.0;
uniform float Y = 0.0;

vec2 OutputColor;

vec2 multiply(vec2 fac1, vec2 fac2) {
	return vec2(0.0, 0.0);
}

vec2 fractal (void){
	return vec2(0.0, 0.0);
}

void main(void) {
	gl_FragColor = vec4(gl_FragCoord.x, 0.5, gl_FragCoord.y,0.0);
}
