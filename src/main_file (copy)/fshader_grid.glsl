#version 410

in vec4 color;
out vec4 frag_color;

void main () 
{
	if(color.a<0.1)
		discard;
  	frag_color = color;
}