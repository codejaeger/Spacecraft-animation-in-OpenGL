#version 330

in vec4 vPosition;
in vec2 texCoord;
in vec4 vNormal;
// in vec4 vColor;

out vec2 tex;
uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

out vec3 normal;
out vec4 eye;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = normalMatrix * vec3(normalize(uModelViewMatrix * vNormal));
  eye = -gl_Position;
  tex = texCoord;
}