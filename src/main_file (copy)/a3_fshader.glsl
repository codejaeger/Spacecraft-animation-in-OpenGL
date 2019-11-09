#version 330

in vec4 fragpos;
in vec4 fragnorm;
in vec2 tex;
in float bt;
out vec4 frag_color;

uniform sampler2D texturun;
uniform sampler2D tex1;
void main () 
{
  vec4 lightPos = vec4(0.0, 0.0, 0.0, 1.0);
  vec4 eyePos = vec4(-1.5, -1.5, -1.5, 1.0);
  vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0);
  vec4 lt_col = vec4(0.8, 0.8, 0.8, 1.0); 
  vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 ambient1 = vec4(0.5, 0.5, 0.5, 1.0);
  vec4 ambient3 = vec4(0.4, 0.4, 0.4, 1.0);
  vec4 specular = vec4(0.5, 0.5, 0.5, 1.0);
  vec4 trans = vec4(1.0,1.0,1.0,0.1);
  float shininess = 0.05;
  vec4 spec = vec4(0.0); 
  
  // Defining Light 
  vec4 lightDir = normalize(lightPos - fragpos); 
  //lightDir = normalize(lightDir);  
  vec4 norm = normalize(fragnorm);
  float dotProduct = dot(norm, lightDir);
  float intensity =  max(0,dotProduct);
  vec4 diff = intensity * lt_col * diffuse;
  vec4 color = texture(texturun, tex);
  vec4 color2 = texture(tex1, tex);

  // Compute specular component only if light falls on vertex
  if(intensity > 0.0)
  {
	vec4 eye = normalize( vec4(-eyePos));
	vec4 h = normalize(lightDir + eye );
   	float intSpec = max(dot(h,fragnorm), 0.0);	
    spec = specular * pow(intSpec, shininess);
  }  	
  if(intensity<=0.0)
  {
  frag_color = color2*(ambient1+diff); // All
  if(bt==2)
  {
    frag_color = color2*(ambient+diff);
  }
  }
  else
  {
  frag_color = color*(ambient1+diff);
  }
  if(bt==1)
  {
    if(color.x<0.2||color.y<0.2||color.z<0.2)
      discard;
    if(intensity<=0.0)
      frag_color = (color*(ambient3+diff));
    else
      frag_color = (color*(ambient1+diff));
  }
  if(bt==3)
  {
  frag_color = vec4(1.0, 0, 0, 1.0);
  }
  if(bt==5)
  {
  frag_color = vec4(1.0,0.0,0.0,1.0);
  }
}
