#version 330

in vec4 vPosition;
in vec3 texCoord;
in vec4 vNormal;

out vec2 tex;
out vec4 fragpos;
out vec4 fragnorm;
out float bt;
uniform mat4 uModelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 modelMatrix;
// in int perPixel;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  tex = vec2(texCoord.x,texCoord.y);
  bt = texCoord.z;
  fragpos = modelMatrix * vPosition;
  fragnorm = normalize(normalMatrix * normalize(vNormal));
}
