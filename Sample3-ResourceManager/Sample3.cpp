#include "Sample3.h"

#include <iostream>

#include "LoadImage.h"

using namespace std;

Sample3::Sample3()
{
	mWindow = NULL;
	quit = false;
	time = 0;
	mode = 1;
}

Sample3::~Sample3()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_Quit();
}

bool Sample3::start(const char* title, const int screenWidth, const int screenHeight)
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int imgFlag = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlag) & imgFlag))
		cout << "IMG INIT Fail! Error:" << IMG_GetError() << endl;

	SDL_GL_SetSwapInterval(0);

	start();

	SDL_Event e;

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

void Sample3::start()
{
	glClearColor(0.0f, 0.0f, 0.0, 1.0f);

	sp.push_back(new Sprite());
	sp.back()->init(-1.0f,0.0f,1.0f,1.0f,"Texture/icon.png");

	sp.push_back(new Sprite());
	sp.back()->init(0.0f,0.0f,1.0f,1.0f,"Texture/icon.png");

	sp.push_back(new Sprite());
	sp.back()->init(-1.0f,-1.0f,1.0f,1.0f,"Texture/icon.png");

	sp.push_back(new Sprite());
	sp.back()->init(0.0f,-1.0f,1.0f,1.0f,"Texture/icon.png");
	
	shader.compileShaders("Shader/Sample2Shader.vs", "Shader/Sample2Shader.fs");
	shader.addAttribute("Position");
	shader.addAttribute("Color");
	shader.addAttribute("UV");
	shader.linkShader();

	//playerTexture = LoadImage::load("Texture/icon.png");
}

void Sample3::input(SDL_Event e)
{
	if(e.type == SDL_KEYDOWN)
	{
		if(e.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = true;
		}
	}
}

void Sample3::update()
{
	time += 0.01f;

	if(time >= 50)
	{
		mode *= -1;
		time = 0;
	}

	shader.use();

	GLuint texUniform = shader.getUniformLocation("myTex");
	glUniform1i(texUniform, 0);

	GLuint timeUniform = shader.getUniformLocation("time");
	glUniform1f(timeUniform, time);

	GLuint modeUniform = shader.getUniformLocation("mode");
	glUniform1i(modeUniform, mode);

	for(int i = 0; i < sp.size(); i++)
	{
		sp[i]->draw();
	}

	shader.unUse();
}


int main(int argc, char* argv[])
{
	Sample3 app;

	app.start("Sample3 Window", 1024, 768);

	return 0;
}