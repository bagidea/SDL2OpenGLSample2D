#ifndef Sample7_H
#define Sample7_H

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>

#include "SpriteBatch.h"
#include "GLSLprogram.h"
#include "Camera2D.h"

using namespace std;

struct Player
{
	GLfloat x;
	GLfloat y;

	void setPosition(GLfloat X, GLfloat Y)
	{
		x = X;
		y = Y;
	}
};

class Sample7
{
public:
	Sample7();
	~Sample7();

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

	vector<Player> playerList;
};

#endif