#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in float a_TexIndex;
layout(location = 3) in float a_TilingFactor;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec2 TexCoord;
	float TexIndex;
	float TilingFactor;
};

layout (location = 0) out VertexOutput Output;

void main()
{
	Output.TexCoord = a_TexCoord;
	Output.TexIndex = a_TexIndex;
	Output.TilingFactor = a_TilingFactor;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}