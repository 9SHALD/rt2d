#include "Floor.h"


MyFloor::MyFloor() : Entity()
{
	this->addSprite("assets/square_filled.tga");
	this->sprite()->color = GREEN;
}

MyFloor::~MyFloor()
{

}

void MyFloor::update(float deltaTime)
{

}