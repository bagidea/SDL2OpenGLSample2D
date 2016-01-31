#ifndef Sample8_H
#define Sample8_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>

#include "SpriteBatch.h"
#include "GLSLprogram.h"
#include "Camera2D.h"
#include "Bullet.h"

using namespace std;

class Sample8
{
public:
	Sample8();
	~Sample8();

	bool start(const char* title, const int screenWidth, const int screenHeight);
	void calculateFPS();
private:
	bool quit;

	void start();
	void input(SDL_Event e);
	void update();

	SDL_Window* mWindow;
	SDL_GLContext mGl;

	SpriteBatch spb;
	GLSLprogram shader;

	float FPS;
	float frameTime;
	float maxFPS;

	Camera2D cam;

	vector<Bullet> bullets;
};

#endif