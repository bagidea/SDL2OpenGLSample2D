#include "Sample1.h"

#include <iostream>

using namespace std;

Sample1::Sample1()
{
	mWindow = NULL;
	time = 0;
	mode = 1;
}

Sample1::~Sample1()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_Quit();
}

bool Sample1::start(const char* title, const int screenWidth, const int screenHeight)
{
	SDL_Init(SDL_INIT_VIDEO);

	mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	if(mWindow == nullptr)
		cout << "GL Context not create!" << endl;
	
	mGl = SDL_GL_CreateContext(mWindow);
	if(mGl == nullptr)
		cout << "GL Context not create!" << endl;

	GLenum err = glewInit();
	if(err != GLEW_OK)
		cout << "GL Context initialized error!" << endl;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	start();

	SDL_Event e;
	bool quit = false;

	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}else{
				input(e);
			}
		}

		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();

		SDL_GL_SwapWindow(mWindow);
	}

	return true;
}

void Sample1::start()
{
	glClearColor(0.0f, 0.0f, 0.0, 1.0f);
	
	sp.init(-1.0f,-1.0f,2.0f,2.0f);
	
	shader.compileShaders("Shader/Sample1Shader.vs", "Shader/Sample1Shader.fs");
	shader.addAttribute("Position");
	shader.addAttribute("Color");
	shader.linkShader();
}

void Sample1::input(SDL_Event e)
{
	if(e.type == SDL_MOUSEMOTION)
	{
		cout << e.motion.x << " : " << e.motion.y << endl;
	}
}

void Sample1::update()
{
	time += 0.01f;

	if(time >= 50)
	{
		mode *= -1;
		time = 0;
	}

	shader.use();

	GLuint timeUniform = shader.getUniformLocation("time");
	glUniform1f(timeUniform, time);

	GLuint modeUniform = shader.getUniformLocation("mode");
	glUniform1i(modeUniform, mode);

	sp.draw();
	shader.unUse();
}

int main(int argc, char* argv[])
{
	Sample1 app;

	app.start("Sample1 Window", 1024, 768);

	return 0;
}