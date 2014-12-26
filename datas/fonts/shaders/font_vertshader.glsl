#version 120

void main (void) {
	// Transforme the vertex position
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Transforme the texture coordinates
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	// Transmit the color
	gl_FrontColor = gl_Color;
}