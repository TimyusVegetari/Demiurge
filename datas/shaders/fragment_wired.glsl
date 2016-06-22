#version 140

uniform vec4 v4Color;

void main (void)
{
	gl_FragColor = v4Color;
	//gl_FragColor = vec4(1.f, 1.f, 1.f, 1.f);
}
