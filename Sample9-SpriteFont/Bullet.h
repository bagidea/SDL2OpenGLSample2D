#ifndef BULLET_H
#define BULLET_H

#include <glm\glm.hpp>

#include "SpriteBatch.h"

class Bullet
{
public:
	Bullet(glm::vec2 Position, glm::vec2 Direction, float Speed, float LiftTime);
	~Bullet();

	void draw(SpriteBatch& spriteBatch);
	bool update();
private:
	float liftTime;
	float speed;
	glm::vec2 direction;
	glm::vec2 position;
};

#endif