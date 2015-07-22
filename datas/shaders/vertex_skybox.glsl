#version 120

uniform mat4 mvpMatrix;
varying vec3 TexCoords;

void main (void)
{
  gl_Position = mvpMatrix * vec4(gl_Vertex.xyz, 1.0);
  gl_TexCoord[0] = gl_MultiTexCoord0;
  TexCoords = gl_TexCoord[0].xyz;
}