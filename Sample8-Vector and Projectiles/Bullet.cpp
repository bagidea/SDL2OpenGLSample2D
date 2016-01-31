#include "Bullet.h"

#include "ResourceManager.h"

Bullet::Bullet(glm::vec2 Position, glm::vec2 Direction, float Speed, float LiftTime)
{
	liftTime = LiftTime;
	speed = Speed;
	direction = Direction;
	position = Position;
}

Bullet::~Bullet()
{
}

void Bullet::draw(SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLtexture texture = ResourceManager::getTexture("Texture/icon.png");

	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	spriteBatch.draw(glm::vec4(position.x, position.y, 30.0f, 30.0f), uv, texture.id, 0, color);
}

bool Bullet::update()
{
	position += direction * speed;
	
	liftTime--;
	if(liftTime == 0)
		return false;
	return true;
}