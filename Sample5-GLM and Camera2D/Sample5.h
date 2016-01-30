#ifndef Sample5_H
#define Sample5_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLSLprogram.h"
#include "Camera2D.h"

using namespace std;

class Sample5
{
public:
	Sample5();
	~Sample5();

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

	Camera2D cam;
};

#endif