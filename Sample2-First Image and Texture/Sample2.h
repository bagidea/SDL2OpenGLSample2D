#ifndef SAMPLE2_H
#define SAMPLE2_H

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLSLprogram.h"
#include "GLtexture.h"

class Sample2
{
public:
	Sample2();
	~Sample2();

	void start(const char* title, const int screenWidth, const int screenHeight);
private:
	bool quit;

	void start();
	void input(SDL_Event e);
	void update();

	SDL_Window* mWindow;
	SDL_GLContext mGl;

	Sprite sp;
	GLSLprogram shader;

	GLfloat time;
	GLint mode;

	GLtexture playerTexture;
};

#endif