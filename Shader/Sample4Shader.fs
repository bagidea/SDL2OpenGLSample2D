#version 400 core

in vec4 fColor;
in vec2 fUV;

out vec4 color;

uniform sampler2D myTex;

void main()
{
	vec4 tex = texture(myTex, fUV);

	color = fColor * tex;
}