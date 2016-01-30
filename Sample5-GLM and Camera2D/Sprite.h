#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <GL\glew.h>

#include "Vertex.h"
#include "GLtexture.h"

using namespace std;

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(GLfloat x, GLfloat y, GLfloat width, GLfloat height, string imagePath);
	void draw();
private:
	GLfloat _x, _y, _width, _height;
	GLuint id;

	GLtexture texture;
};

#endif