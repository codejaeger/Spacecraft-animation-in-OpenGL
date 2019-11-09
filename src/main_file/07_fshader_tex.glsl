#version 330


out vec4 frag_color;

uniform mat4 viewMatrix;
uniform sampler2D texture;
in vec2 tex;
in vec3 normal;
in vec4 eye;
void main () 
{
  // frag_color = texture2D(texture, tex);	
  // Defining Materials
  vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0); 
  vec4 ambient = vec4(0.3, 0.3, 0.3, 1.0);
  vec4 specular = vec4(0.3, 0.3, 0.3, 1.0);
  float shininess = 0.1;
  vec4 spec = vec4(0.0);

  // Defining Light 
  vec4 lightPos = vec4(5.0, 0.0, 3.5, 0.0);
  vec3 lightDir = vec3(viewMatrix * lightPos);  // Transforms with camera
  lightDir = normalize( vec3(lightDir));  

  //Diffuse
  vec3 n = normalize(vec3(normal));
  float dotProduct = dot(n, lightDir);
  float intensity =  max( dotProduct, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity > 0.0)
  {
	vec3 e = normalize(vec3(eye));
	vec3 h = normalize(lightDir + e );
   	float intSpec = max(dot(h,n), 0.0);	
        spec = specular * pow(intSpec, shininess);
  }

  vec4 COLOR = texture2D(texture, tex);
  // intensity = 20*intensity;

  vec4 color = max((intensity * diffuse  + spec)*COLOR, ambient*COLOR); // All
 //vec4 color = intensity * diffuse; // Only Diffuse  
  frag_color = color;
}
