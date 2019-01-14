#include "bullet.h"
class myscene;

MyBullet::MyBullet() : Entity()
{
	this->addSprite("assets/bullet.tga");
	_velocity = Vector2(0,0);
}

MyBullet::~MyBullet()
{

}

void MyBullet::update(float deltaTime)
{
	if (this->position.x >= 0 && this->position.x <= SWIDTH) {
		_velocity.y += 0.05;
		
	}
	this->position += _velocity;
	this->rotation.z = _velocity.getAngle();
}

void MyBullet::move(float speed)
{
	reset();
	_velocity.x += cos(this->rotation.z) * speed;
	_velocity.y += sin(this->rotation.z) * speed;
}

void MyBullet::move(float degrees, float speed) {
	reset();
	float radians = degrees * (PI / 180);
	_velocity.x += cos(radians) * speed;
	_velocity.y += sin(radians) * speed;

}

void MyBullet::reset()
{
	_velocity.x = 0;
	_velocity.y = 0;
}
