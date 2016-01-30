#include "Camera2D.h"

Camera2D::Camera2D()
{
	screenWidth = 0;
	screenHeight = 0;
	needUpdate = true;
	scale = 1.0f;
	position = glm::vec2(0.0f, 0.0f);
	camMatrix = glm::mat4(1.0f);
	orthoMatrix = glm::mat4(1.0f);
}

Camera2D::~Camera2D()
{
}

void Camera2D::init(int _screenWidth, int _screenHeight)
{
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
}

void Camera2D::update()
{
	if(needUpdate)
	{
		glm::vec3 translate(-position.x, -position.y, 0.0f);
		//glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0.0f);
		camMatrix = glm::translate(orthoMatrix, translate);
		glm::vec3 scale(scale, scale, 0.0f);
		camMatrix = glm::scale(camMatrix, scale);
		//camMatrix = glm::scale(glm::mat4(1.0f), scale) * camMatrix;
		needUpdate = false;
	}
}