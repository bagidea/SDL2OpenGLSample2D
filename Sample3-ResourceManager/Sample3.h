#ifndef SAMPLE3_H
#define SAMPLE3_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLSLprogram.h"

using namespace std;

class Sample3
{
public:
	Sample3();
	~Sample3();

	bool start(const char* title, const int screenWidth, const int screenHeight);
private:
	bool quit;

	void start();
	void input(SDL_Event e);
	void update();

	SDL_Window* mWindow;
	SDL_GLContext mGl;

	vector<Sprite*> sp;
	GLSLprogram shader;

	GLfloat time;
	GLint mode;
};

#endif