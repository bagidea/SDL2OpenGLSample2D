#ifndef VERTEX_H
#define VERTEX_H

#include <GL\glew.h>
#include <cstddef>

struct Position
{
	GLfloat x;
	GLfloat y;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV
{
	GLfloat u;
	GLfloat v;
};

struct Vertex
{
	Position position;
	Color color;
	UV uv;

	void setPosition(GLfloat x, GLfloat y)
	{
		position.x = x;
		position.y = y;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(GLfloat u, GLfloat v)
	{
		uv.u = u;
		uv.v = v;
	}
};

#endif