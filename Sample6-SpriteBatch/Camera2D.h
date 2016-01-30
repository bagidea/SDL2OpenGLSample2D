#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void init(int _screenWidth, int _screenHeight);

	void update();

	void setScale(float _scale){scale = _scale; needUpdate = true;}
	float getScale(){return scale;}

	void setPosition(const glm::vec2& _position){position = _position; needUpdate = true;}
	glm::vec2 getPosition(){return position;}

	glm::mat4 getCameraMatrix(){return camMatrix;}
private:
	int screenWidth, screenHeight;
	bool needUpdate;
	float scale;
	glm::vec2 position;
	glm::mat4 camMatrix;
	glm::mat4 orthoMatrix;
};

#endif