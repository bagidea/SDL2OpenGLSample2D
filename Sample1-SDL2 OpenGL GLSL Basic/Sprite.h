#ifndef SPRITE_H
#define SPRITE_H

#include <GL\glew.h>

#include "Vertex.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	void draw();

private:
	GLfloat _x, _y, _width, _height;
	GLuint id;
};

#endif