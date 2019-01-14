#include "tank.h"

MyTank::MyTank() : Entity()
{
	this->addSprite("assets/tank.tga");
	this->sprite()->color = WHITE;

	//creates the barrel of the tank
	barrel = new MyBarrel();
	this->addChild(barrel);

	shot = 0;
	barrelrot = barrel->rotation.z;
}

MyTank::~MyTank()
{
	this->removeChild(barrel);
	delete barrel;
	
}

void MyTank::update(float deltaTime) 
{
	barrel->sprite()->color = this->sprite()->color;
	barrelrot = barrel->rotation.z;
}


// movement for the tank and the barrel
void MyTank::movement()
{
	if (position.x >= 17) {
		if (input()->getKey(KeyCode::A)) {
			position.x -= 0.5;
		}
	}
	if (position.x <= SWIDTH - 17) {
		if (input()->getKey(KeyCode::D)) {
			position.x += 0.5;
		}
	}
	if (barrel->rotation.z > -3.16){
		if (input()->getKey(KeyCode::W)) {
			barrel->rotation.z -= 0.01;
		}
	}
	if (barrel->rotation.z < 0) {
		if (input()->getKey(KeyCode::S)) {
			barrel->rotation.z += 0.01;
		}
	}
	if (input()->getKey(KeyCode::Space)) {
		if (shot == 0) {
			std::cout << "Shot fired" << std::endl;
			shot = 1;
		}
	}
	if (shot == 1) {
		for (size_t i = 0; i < 30; i++){
			if (i == 30) {
				shot = 0;
				std::cout << "Shot Ready" << std::endl;
			}
		}
	}
}

// gravity for the tank
void MyTank::gravity()
{
	position.y += 1;
}

void MyTank::setBarrelRot(float a) {
	barrel->rotation.z = a;
}
