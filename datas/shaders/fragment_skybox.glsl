#version 140

uniform samplerCube cubemap;
varying vec3 TexCoords;

void main (void)
{
	gl_FragColor = textureCube(cubemap, TexCoords);
}
