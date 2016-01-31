#include "Sample10.h"

#include <iostream>
#include <sstream>

#include "ResourceManager.h"

using namespace std;

const int screenWidth = 1024;
const int screenHeight = 768;

Sample10::Sample10()
{
	mWindow = NULL;
	quit = false;
	maxFPS = 60.0f;

	ballAngle = 0.0f;
}

Sample10::~Sample10()
{
	TTF_CloseFont(ResourceManager::getFont("Font/SIXTY.ttf", 18));
	TTF_CloseFont(ResourceManager::getFont("Font/SIXTY.ttf", 28));

	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_Quit();
}

bool Sample10::start(const char* title, const int screenWidth, const int screenHeight)
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

	if(TTF_Init() == -1)
        cout << "TTF INIT Fail! Error:" << TTF_GetError() << endl;

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

void Sample10::calculateFPS()
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

void Sample10::start()
{
	glClearColor(0.0f, 0.0f, 0.0, 1.0f);

	cam.init(screenWidth, screenHeight);
	
	camUI.init(screenWidth, screenHeight);
	camUI.setPosition(glm::vec2(screenWidth / 2, screenHeight / 2));

	spb.init();
	spbUI.init();
	
	shader.compileShaders("Shader/Sample4Shader.vs", "Shader/Sample4Shader.fs");
	shader.addAttribute("Position");
	shader.addAttribute("Color");
	shader.addAttribute("UV");
	shader.linkShader();

	txt1.setFont(ResourceManager::getFont("Font/SIXTY.ttf", 18));
	txt1.setText("Rotation from Angle");
	txt1.setPosition(glm::vec2(-60.0f, 120.0f));

	txt2.setFont(ResourceManager::getFont("Font/SIXTY.ttf", 18));
	txt2.setText("Direction : 0, 0");
	txt2.setPosition(glm::vec2(-350.0f, 250.0f));

	txt3.setFont(ResourceManager::getFont("Font/SIXTY.ttf", 18));
	txt3.setText("Direction : 0, 0");
	txt3.setPosition(glm::vec2(150.0f, 250.0f));

	txt4.setFont(ResourceManager::getFont("Font/SIXTY.ttf", 18));
	txt4.setText("Direction : 0, 0");
	txt4.setPosition(glm::vec2(-350.0f, -190.0f));

	txt5.setFont(ResourceManager::getFont("Font/SIXTY.ttf", 18));
	txt5.setText("Direction : 0, 0");
	txt5.setPosition(glm::vec2(150.0f, -190.0f));

	text.setFont(ResourceManager::getFont("Font/SIXTY.ttf", 28));
	text.setText("Sample10 Rotation from Angle and Direction");

	SDL_Color color = {0x00, 0xFF, 0x00, 0xFF};
	text.SetColor(color);
}

void Sample10::input(SDL_Event e)
{
	float speedCam = 10.0f;

	lookat = cam.screenToWorldPoint(glm::vec2(e.motion.x, e.motion.y));

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

void Sample10::update()
{
	cam.update();
	camUI.update();

	txt1.update();
	txt2.update();
	txt3.update();
	txt4.update();
	txt5.update();
	text.update();

	shader.use();

	GLuint texUniform = shader.getUniformLocation("myTex");
	glUniform1i(texUniform, 0);

	GLuint pLocation = shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = cam.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	spb.begin();

	glm::vec4 pos(-128.0f, -128.0f, 256.0f, 256.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLtexture texture = ResourceManager::getTexture("Texture/Aball.png");

	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spb.draw(pos, uv, texture.id, 0, color, ballAngle);

	static GLtexture texture2 = ResourceManager::getTexture("Texture/G.png");

	glm::vec2 dir1 = glm::normalize(lookat - glm::vec2(-300.0f, 250.0f - 64.0f));
	glm::vec2 dir2 = glm::normalize(lookat - glm::vec2(300.0f, 250.0f - 64.0f));
	glm::vec2 dir3 = glm::normalize(lookat - glm::vec2(-300.0f, -250.0f));
	glm::vec2 dir4 = glm::normalize(lookat - glm::vec2(300.0f, -250.0f));

	spb.draw(glm::vec4(-300.0f, 250.0f - 64.0f, 64.0f, 64.0f), uv, texture2.id, 0, color, dir1);
	spb.draw(glm::vec4(300.0f - 64.0f, 250.0f - 64.0f, 64.0f, 64.0f), uv, texture2.id, 0, color, dir2);
	spb.draw(glm::vec4(-300.0f, -250.0f, 64.0f, 64.0f), uv, texture2.id, 0, color, dir3);
	spb.draw(glm::vec4(300.0f - 64.0f, -250.0f, 64.0f, 64.0f), uv, texture2.id, 0, color, dir4);

	txt1.draw(spb);

	ostringstream txt;

	txt << "Direction : " <<  dir1.x << ", " << dir1.y;
	txt2.setText(txt.str());
	txt2.draw(spb);

	txt.str("");

	txt << "Direction : " <<  dir2.x << ", " << dir2.y;
	txt3.setText(txt.str());
	txt3.draw(spb);

	txt.str("");

	txt << "Direction : " <<  dir3.x << ", " << dir3.y;
	txt4.setText(txt.str());
	txt4.draw(spb);

	txt.str("");

	txt << "Direction : " <<  dir4.x << ", " << dir4.y;
	txt5.setText(txt.str());
	txt5.draw(spb);

	txt.str("");

	spb.end();
	spb.render();

	ballAngle -= 0.02f;
	
	////////////////

	cameraMatrix = camUI.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	spbUI.begin();

	text.setPosition(glm::vec2((screenWidth / 2) - (text.getWidth() / 2), 10.0f));
	text.draw(spbUI);

	spbUI.end();
	spbUI.render();

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
	Sample10 app;

	app.start("Sample10 Window", screenWidth, screenHeight);

	return 0;
}