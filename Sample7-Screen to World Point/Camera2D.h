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

	glm::vec2 screenToWorldPoint(glm::vec2 pos)
	{
		pos -= glm::vec2(screenWidth / 2, screenHeight / 2);
		pos /= scale;
		pos += glm::vec2(position.x, -position.y);

		return glm::vec2(pos.x, -pos.y);
	}
private:
	int screenWidth, screenHeight;
	bool needUpdate;
	float scale;
	glm::vec2 position;
	glm::mat4 camMatrix;
	glm::mat4 orthoMatrix;
};

#endif