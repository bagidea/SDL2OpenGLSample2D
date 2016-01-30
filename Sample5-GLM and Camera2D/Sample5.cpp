#include "Sample5.h"

#include <iostream>

#include "LoadImage.h"

using namespace std;

const int screenWidth = 1024;
const int screenHeight = 768;

Sample5::Sample5()
{
	mWindow = NULL;
	quit = false;
	time = 0;
	mode = 1;
	maxFPS = 60.0f;
}

Sample5::~Sample5()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_Quit();
}

bool Sample5::start(const char* title, const int screenWidth, const int screenHeight)
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

void Sample5::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

	prevTicks = currentTicks;

	int count;
	
	currentFrame++;

	if(currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}else{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for(int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}

	frameTimeAverage /= count;

	if(frameTimeAverage > 0)
	{
		FPS = 1000.0f / frameTimeAverage;
	}else{
		FPS = 60.0f;
	}
}

void Sample5::start()
{
	glClearColor(0.0f, 0.0f, 0.0, 1.0f);

	cam.init(screenWidth, screenHeight);

	sp.push_back(new Sprite());
	sp.back()->init(0.0f, 0.0f,screenWidth / 2, screenHeight / 2,"Texture/icon.png");

	sp.push_back(new Sprite());
	sp.back()->init(screenWidth / 2, 0.0f,screenWidth / 2, screenHeight / 2,"Texture/icon.png");

	sp.push_back(new Sprite());
	sp.back()->init(0.0f, screenHeight / 2, screenWidth / 2, screenHeight / 2,"Texture/icon.png");

	sp.push_back(new Sprite());
	sp.back()->init(screenWidth / 2, screenHeight / 2, screenWidth / 2, screenHeight / 2,"Texture/icon.png");
	
	shader.compileShaders("Shader/Sample3Shader.vs", "Shader/Sample3Shader.fs");
	shader.addAttribute("Position");
	shader.addAttribute("Color");
	shader.addAttribute("UV");
	shader.linkShader();

	cam.setPosition(glm::vec2(GLfloat(screenWidth / 2), GLfloat(screenHeight / 2)));
}

void Sample5::input(SDL_Event e)
{
	float speedCam = 10.0f;

	if(e.type == SDL_KEYDOWN)
	{
		if(e.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = true;
		}
		else if(e.key.keysym.sym == SDLK_w)
		{
			cam.setPosition(cam.getPosition() + glm::vec2(0.0f, speedCam));
		}
		else if(e.key.keysym.sym == SDLK_s)
		{
			cam.setPosition(cam.getPosition() + glm::vec2(0.0f, -speedCam));
		}
		else if(e.key.keysym.sym == SDLK_a)
		{
			cam.setPosition(cam.getPosition() + glm::vec2(-speedCam, 0.0f));
		}
		else if(e.key.keysym.sym == SDLK_d)
		{
			cam.setPosition(cam.getPosition() + glm::vec2(speedCam, 0.0f));
		}
		else if(e.key.keysym.sym == SDLK_q)
		{
			cam.setScale(cam.getScale() + 0.1f);
		}
		else if(e.key.keysym.sym == SDLK_e)
		{
			cam.setScale(cam.getScale() - 0.1f);
		}
	}
}

void Sample5::update()
{
	time += 0.01f;

	if(time >= 50)
	{
		mode *= -1;
		time = 0;
	}

	cam.update();

	shader.use();

	GLuint texUniform = shader.getUniformLocation("myTex");
	glUniform1i(texUniform, 0);

	GLuint timeUniform = shader.getUniformLocation("time");
	glUniform1f(timeUniform, time);

	GLuint modeUniform = shader.getUniformLocation("mode");
	glUniform1i(modeUniform, mode);

	GLuint pLocation = shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = cam.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	for(int i = 0; i < sp.size(); i++)
	{
		sp[i]->draw();
	}

	shader.unUse();

	///////////////// FPS ////////////////////
	float startTicks = SDL_GetTicks();

	calculateFPS();

	static int frameCounter = 0;
	frameCounter++;
	if(frameCounter == 10)
	{
		cout << "FPS: " << FPS << endl;
		frameCounter = 0;
	}

	float frameTicks = SDL_GetTicks() - startTicks;
	if(1000.0f / maxFPS > frameTicks)
		SDL_Delay(1000.0f / maxFPS - frameTicks);
	///////////////// END ////////////////////
}


int main(int argc, char* argv[])
{
	Sample5 app;

	app.start("Sample5 Window", screenWidth, screenHeight);

	return 0;
}