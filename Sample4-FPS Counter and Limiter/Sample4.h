#ifndef Sample4_H
#define Sample4_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLSLprogram.h"

using namespace std;

class Sample4
{
public:
	Sample4();
	~Sample4();

	bool start(const char* title, const int screenWidth, const int screenHeight);
	void calculateFPS();
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

	float FPS;
	float frameTime;
	float maxFPS;
};

#endif