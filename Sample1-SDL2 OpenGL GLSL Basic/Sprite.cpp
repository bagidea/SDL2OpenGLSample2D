#include "Sprite.h"

Sprite::Sprite()
{
	_x = 0;
	_y = 0;
	_width = 0;
	_height = 0;
	id = 0;
}

Sprite::~Sprite()
{
	if(id != 0)
		glDeleteBuffers(1, &id);
}

void Sprite::init(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	if(id == 0)
		glGenBuffers(1, &id);

	_x = x;
	_y = y;
	_width = width;
	_height = height;

	Vertex vertexArr[6];

	vertexArr[0].position.x = _x + _width;
	vertexArr[0].position.y = _y + _height;
	vertexArr[1].position.x = _x;
	vertexArr[1].position.y = _y + _height;
	vertexArr[2].position.x = _x;
	vertexArr[2].position.y = _y;
	vertexArr[3].position.x = _x;
	vertexArr[3].position.y = _y;
	vertexArr[4].position.x = _x + _width;
	vertexArr[4].position.y = _y;
	vertexArr[5].position.x = _x + _width;
	vertexArr[5].position.y = _y + _height;

	for(int i = 0; i < 6; i++)
	{
		vertexArr[i].color.r = 255;
		vertexArr[i].color.g = 0;
		vertexArr[i].color.b = 255;
		vertexArr[i].color.a = 255;
	}

	vertexArr[1].color.r = 0;
	vertexArr[1].color.g = 0;
	vertexArr[1].color.b = 255;
	vertexArr[1].color.a = 255;

	vertexArr[4].color.r = 0;
	vertexArr[4].color.g = 255;
	vertexArr[4].color.b = 0;
	vertexArr[4].color.a = 255;

	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArr), vertexArr, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}