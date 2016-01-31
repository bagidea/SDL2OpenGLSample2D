#include "Sample8.h"

#include <iostream>

#include "ResourceManager.h"

using namespace std;

const int screenWidth = 1024;
const int screenHeight = 768;

Sample8::Sample8()
{
	mWindow = NULL;
	quit = false;
	maxFPS = 60.0f;
}

Sample8::~Sample8()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_Quit();
}

bool Sample8::start(const char* title, const int screenWidth, const int screenHeight)
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

void Sample8::calculateFPS()
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

void Sample8::start()
{
	glClearColor(0.0f, 0.0f, 0.0, 1.0f);

	cam.init(screenWidth, screenHeight);

	spb.init();
	
	shader.compileShaders("Shader/Sample4Shader.vs", "Shader/Sample4Shader.fs");
	shader.addAttribute("Position");
	shader.addAttribute("Color");
	shader.addAttribute("UV");
	shader.linkShader();
}

void Sample8::input(SDL_Event e)
{
	float speedCam = 10.0f;

	glm::vec2 worldPos = cam.screenToWorldPoint(glm::vec2(e.motion.x, e.motion.y));

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
	else if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
		{
			glm::vec2 playerPosition(-15.0f, -15.0f);
			glm::vec2 direction = glm::vec2(worldPos.x - 15.0f, worldPos.y - 15.0f) - playerPosition;
			direction = glm::normalize(direction);

			bullets.emplace_back(playerPosition, direction, 5.0f, 1000);
		}
	}
}

void Sample8::update()
{
	cam.update();

	for(int i = 0; i < bullets.size();)
	{
		if(!bullets[i].update())
		{
			bullets[i] = bullets.back();
			bullets.pop_back();
		}else{
			i++;
		}
	}

	shader.use();

	GLuint texUniform = shader.getUniformLocation("myTex");
	glUniform1i(texUniform, 0);

	GLuint pLocation = shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = cam.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	spb.begin();

	glm::vec4 pos(-256.0f, -256.0f, 512.0f, 512.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLtexture texture = ResourceManager::getTexture("Texture/Pointer.png");

	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spb.draw(pos, uv, texture.id, 0, color);

	for(int i = 0; i < bullets.size(); i++)
		bullets[i].draw(spb);

	spb.end();
	spb.render();

	shader.unUse();

	///////////////// FPS ////////////////////
	float startTicks = SDL_GetTicks();

	calculateFPS();

	static int frameCounter = 0;
	frameCounter++;
	if(frameCounter == 100)
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
	Sample8 app;

	app.start("Sample8 Window", screenWidth, screenHeight);

	return 0;
}