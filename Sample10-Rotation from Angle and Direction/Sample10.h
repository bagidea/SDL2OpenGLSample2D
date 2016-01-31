#ifndef Sample10_H
#define Sample10_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL\glew.h>

#include "SpriteBatch.h"
#include "GLSLprogram.h"
#include "Camera2D.h"
#include "SpriteFont.h"

using namespace std;

class Sample10
{
public:
	Sample10();
	~Sample10();

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

	float ballAngle;
	glm::vec2 lookat;

	SpriteFont txt1;
	SpriteFont txt2;
	SpriteFont txt3;
	SpriteFont txt4;
	SpriteFont txt5;
	SpriteFont text;
};

#endif