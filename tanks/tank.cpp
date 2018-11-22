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
	// ###############################################################
	// Rotate
	// ###############################################################
	if (input()->getKeyDown(KeyCode::A)) {
		this->rotation.z -= HALF_PI * deltaTime; // 90 deg/sec
		if (this->rotation.z > TWO_PI) {
			this->rotation.z += TWO_PI;
		}
	}
	if (input()->getKeyDown(KeyCode::D)) {
		this->rotation.z += HALF_PI * deltaTime; // 90 deg/sec
		if (this->rotation.z > TWO_PI) {
			this->rotation.z -= TWO_PI;
		}
	}
	/*this->rotation.z += HALF_PI * deltaTime; // 90 deg/sec
	if (this->rotation.z > TWO_PI) {
		this->rotation.z -= TWO_PI;
	}*/
}