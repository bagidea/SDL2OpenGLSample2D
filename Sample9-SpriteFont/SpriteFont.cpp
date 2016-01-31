#include "SpriteFont.h"

SpriteFont::SpriteFont()
{
	position = glm::vec2(0.0f);
	
	_color.r = 0xFF;
	_color.g = 0xFF;
	_color.b = 0xFF;
	_color.a = 0xFF;
	text = "";
}

SpriteFont::~SpriteFont()
{
}

void SpriteFont::setText(string Text)
{
	text = Text;
}

void SpriteFont::setFont(TTF_Font* font)
{
	_font = font;
}

void SpriteFont::setPosition(glm::vec2 Position)
{
	position = Position;
}

glm::vec2 SpriteFont::getPosition()
{
	return position;
}

GLint SpriteFont::getWidth()
{
	return texture.width;
}

GLint SpriteFont::getHeight()
{
	return texture.height;
}

void SpriteFont::SetColor(SDL_Color Color)
{
	_color = Color;
}

SDL_Color SpriteFont::getColor()
{
	return _color;
}

void SpriteFont::update()
{
	SDL_Surface* img = TTF_RenderText_Blended(_font, text.c_str(), _color);

	if(img == NULL)
		cout << "Render SpriteFont failed!" << endl;

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	texture.width = img->w;
	texture.height = img->h;

	SDL_FreeSurface(img);
	img = NULL;
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteFont::draw(SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spriteBatch.draw(glm::vec4(position.x, position.y, texture.width, texture.height), uv, texture.id, 0, color);
}