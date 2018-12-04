#include "tank.h"

MyTank::MyTank() : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;
}

MyTank::~MyTank()
{

}

void MyTank::update(float deltaTime)
{

}

void MyTank::movement()
{
	if (position.x >= 17) {
		if (input()->getKey(KeyCode::A)) {
			position.x -= 1;
		}
	}
	if (position.x <= SWIDTH - 17) {
		if (input()->getKey(KeyCode::D)) {
			position.x += 1;
		}
	}
}
