#ifndef Sample9_H
#define Sample9_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL\glew.h>

#include "SpriteBatch.h"
#include "GLSLprogram.h"
#include "Camera2D.h"
#include "Bullet.h"
#include "SpriteFont.h"

using namespace std;

class Sample9
{
public:
	Sample9();
	~Sample9();

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
	SpriteBatch spbUI;
	GLSLprogram shader;

	float FPS;
	float frameTime;
	float maxFPS;

	Camera2D cam;
	Camera2D camUI;

	vector<Bullet> bullets;

	SpriteFont sampleText;
	SpriteFont sampleTextUI;
	SpriteFont sampleTextUI2;
};

#endif