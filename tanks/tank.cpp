#include "tank.h"
#include "myscene.h"
#include "floor.h"
#include "barrel.h"

MyTank::MyTank() : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;

	barrel = new MyBarrel();
	barrel->sprite()->color = this->sprite()->color;

	this->addChild(barrel);
}

MyTank::~MyTank()
{
	this->removeChild(barrel);
	delete barrel;
}

void MyTank::update(float deltaTime)
{
	barrel->sprite()->color = this->sprite()->color;
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

void MyTank::gravity()
{
	position.y += 1;
}


