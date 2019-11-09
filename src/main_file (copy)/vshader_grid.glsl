#version 410

in vec3 vPosition;
in vec4 vColor;
out vec4 color;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vec4(vPosition, 1.0);
  color = vColor;
}