#ifndef SPRITE_FONT_H
#define SPRITE_FONT_H

#include <iostream>
#include <string>
#include <glm\glm.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <GL\glew.h>

#include "SpriteBatch.h"
#include "GLtexture.h"

using namespace std;

class SpriteFont
{
public:
	SpriteFont();
	~SpriteFont();

	void setText(string Text);
	void setFont(TTF_Font* font);

	void setPosition(glm::vec2 Position);
	glm::vec2 getPosition();

	GLint getWidth();
	GLint getHeight();

	void SetColor(SDL_Color Color);
	SDL_Color getColor();

	void update();
	void draw(SpriteBatch& spriteBatch);
private:
	GLtexture texture;
	glm::vec2 position;

	SDL_Color _color;
	string text;
	TTF_Font* _font;
};

#endif
