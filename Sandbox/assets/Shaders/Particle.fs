#version 450 core

layout(location = 0) out vec4 color;

layout(std140, binding = 1) uniform Particle
{
	vec4 u_Color;
};

void main()
{
    color = u_Color;
}