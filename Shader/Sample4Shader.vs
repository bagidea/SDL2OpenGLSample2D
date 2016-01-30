#version 400 core

layout (location = 0) in vec2 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 UV;

out vec4 fColor;
out vec2 fUV;

uniform mat4 P;

void main()
{
	gl_Position.xy = (P * vec4(Position, 0.0f, 1.0f)).xy;
	gl_Position.z = 0.0f;
	gl_Position.w = 1.0f;

	fColor = Color;

	fUV = vec2(UV.x, 1.0f - UV.y);;
}