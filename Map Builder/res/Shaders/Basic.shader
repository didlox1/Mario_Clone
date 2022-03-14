#shader vertex
#version  330 core 

layout(location = 0) in vec4 position;    //vec4 couse gl_Position needs to be in 4 dimension vertex
layout(location = 1) in vec2 texcoord;
out vec2 Texcoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position; 
	Texcoord = texcoord;
};

#shader fragment
#version  330 core 

layout(location = 0) out vec4 color;
in vec2 Texcoord;

uniform sampler2D tex;

void main()
{
	color = vec4(texture(tex, Texcoord));
};