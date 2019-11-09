#version 330

in vec4 vPosition;
in vec2 texCoord;
in vec3 vNormal;
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
  normal = vec3(uModelViewMatrix * vec4(normalMatrix * normalize(vNormal), 1));
  eye = -gl_Position;
  tex = texCoord;
}