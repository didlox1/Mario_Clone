#shader vertex
#version  330 core 

layout(location = 0) in vec4 position;    //vec4 couse gl_Position needs to be in 4 dimension vertex
layout(location = 1) in vec2 texcoord1;  
layout(location = 2) in vec2 texcoord2;
out vec2 Texcoord1;
out vec2 Texcoord2;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position; 
	Texcoord1 = texcoord1;
	Texcoord2 = texcoord2;
};

#shader fragment
#version  330 core 

layout(location = 0) out vec4 color;
in vec2 Texcoord1;
in vec2 Texcoord2;
uniform sampler2D tex;
uniform int faceing;

void main()
{	
	if(faceing == 1) 
	{
		color = vec4(texture(tex, Texcoord1));
	}
	else
	{
		color = vec4(texture(tex, Texcoord2));
	}
};