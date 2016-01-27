#version 400 core

in vec2 fPosition;
in vec4 fColor;
in vec2 fUV;

out vec4 color;

uniform float time;
uniform int mode;
uniform sampler2D myTex;

void main()
{
	vec4 diff;

	if(mode == 1)
	{
		diff = color = fColor + vec4(1.0f * (cos(time) + 1.0f) * 0.5,
							  1.0f * (cos(time + 2.0f) + 1.0f) * 0.5,
							  1.0f * (cos(time + 1.0f) + 1.0f) * 0.5, 1.0f);
	}else{
		diff = color = vec4(fColor.r *(cos(fPosition.x + time) + 1.0f) * 0.5f,
					 fColor.g *(cos(fPosition.y + time) + 1.0f) * 0.5f,
					 fColor.b *(cos(fPosition.x * 0.4f + time) + 1.0f) * 0.5f, 1.0f);
	}

	vec4 tex = texture(myTex, fUV);

	color = diff * tex;
}