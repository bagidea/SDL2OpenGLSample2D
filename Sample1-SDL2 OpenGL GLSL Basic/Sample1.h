#ifndef SAMPLE1_H
#define SAMPLE1_H

#include <SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLSLprogram.h"

class Sample1
{
public:
	Sample1();
	~Sample1();

	bool start(const char* title, const int screenWidth, const int screenHeight);
private:
	void start();
	void input(SDL_Event e);
	void update();

	SDL_Window* mWindow;
	SDL_GLContext mGl;

	Sprite sp;
	GLSLprogram shader;

	GLfloat time;
	GLint mode;
};

#endif