#version 120

uniform mat4 mvpMatrix;

void main (void)
{
  gl_Position = mvpMatrix * vec4(gl_Vertex.xyz, 1.0);
}