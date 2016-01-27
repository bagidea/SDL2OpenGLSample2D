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

	vertexArr[0].setPosition(_x + _width, _y + _height);
	vertexArr[0].setUV(1.0f, 1.0f);
	vertexArr[1].setPosition(_x, _y + _height);
	vertexArr[1].setUV(0.0f, 1.0f);
	vertexArr[2].setPosition(_x, _y);
	vertexArr[2].setUV(0.0f, 0.0f);
	vertexArr[3].setPosition(_x, _y);
	vertexArr[3].setUV(0.0f, 0.0f);
	vertexArr[4].setPosition(_x + _width , _y);
	vertexArr[4].setUV(1.0f, 0.0f);
	vertexArr[5].setPosition(_x + _width, _y + height);
	vertexArr[5].setUV(1.0f, 1.0f);

	for(int i = 0; i < 6; i++)
	{
		vertexArr[i].setColor(255, 0, 0, 255);
	}

	vertexArr[1].setColor(0, 0, 255, 255);
	vertexArr[1].setColor(0, 255, 0, 255);

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
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}