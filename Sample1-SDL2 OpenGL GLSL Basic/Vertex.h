#ifndef VERTEX_H
#define VERTEX_H

#include <GL\glew.h>
#include <cstddef>

struct Vertex
{
	struct Position
	{
		GLfloat x;
		GLfloat y;
	}position;

	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	}color;
};

#endif