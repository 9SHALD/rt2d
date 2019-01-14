/*				*
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	t.start();

	// create a single instance of all entities on the screen.
	tank = new MyTank();
	tank->position = Point2(SWIDTH / 4, SHEIGHT / 1.5);
	tank2 = new MyTank();
	tank2->position = Point2(SWIDTH / 4 * 3, SHEIGHT / 1.5);
	floor = new MyFloor();
	floor->position = Point2(SWIDTH / 2, SHEIGHT / 1.2);
	bullet = new MyBullet();
	bullet->position = Point2(-1, -1);
	bullet->sprite()->color = WHITE;

	
	// sets the scale of all objects
	tank->scale = Point(0.2f, 0.2f);
	tank2->scale = Point(0.2f, 0.2f);
	floor->scale = Point((SWIDTH / 2), 0.2f);
	bullet->scale = Point2(0.1f, 0.1f);
	tank2->setBarrelRot(-PI);
	player = 1;
	playerShot = false;


	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(tank);
	this->addChild(tank2);
	this->addChild(floor);
	this->addChild(bullet);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(tank);
	this->removeChild(tank2);
	this->removeChild(floor);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete tank;
	delete tank2;
	delete floor;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	//std::cout << tank->getHealth() << std::endl;
	//std::cout << bullet->getDamage() << std::endl;
	
	// ###############################################################
	// calls the player movement script
	// ###############################################################
	playerMove();

	// ###############################################################
	// checks if the bullet hits the ground;
	// ###############################################################
	if (isGrounded(bullet, floor)) {
		bulletReset();
	}
	
	// ###############################################################
	// checks if player is grounded. if not grounded adds gravity
	// ###############################################################
	if (!isGrounded(tank, floor)) {
		tank->gravity();	
	}
	if (!isGrounded(tank2, floor)) {
		tank2->gravity();
	}
	bulletOnScreen();
}


// ###############################################################
// isGrounded checks if a object is hitting the floor/ground
// ###############################################################
bool MyScene::isGrounded(Entity* a, Entity* b)
{
	int aPos = a->position.y + (a->sprite()->height() * a->scale.y) / 2;
	int bPos = b->position.y - (b->sprite()->height() * b->scale.y) / 2;
	if (aPos > bPos) {
		return true;
	}
	else {
		return false;
	}
}


// ###############################################################
// changes wich players turn it is
// ###############################################################
void MyScene::playerMove()
{
	switch (player) {
	case 1:
		if (isGrounded(tank, floor)) {
			if (playerShot == false) {
				tank->movement();
				if (input()->getKeyDown(KeyCode::Space)) {
					bullet->position = tank->position;
					bullet->rotation.z = tank->barrelrot;
					bullet->move(5);
					playerShot = true;
				}
			}
		}
		if (collision(bullet, tank2)) {
			bulletReset();
		}
		break;
	case 2:
		if (isGrounded(tank2, floor)) {
			if (playerShot == false) {
				tank2->movement();
				if (input()->getKeyDown(KeyCode::Space)) {
					bullet->position = tank2->position;
					bullet->rotation.z = tank2->barrelrot;
					bullet->move(5);
					playerShot = true;
				}
			}
		}
		if (collision(bullet, tank)) {
			bulletReset();
		}
		break;
	}
}

void MyScene::playerSwitch() {
	if (player == 1) {
		player = 2;
	} else if (player == 2) {
		player = 1;
	}
}

// ###############################################################
// checks if bullet is on screen. if not reset bullet
// ###############################################################
void MyScene::bulletOnScreen() {
	if (playerShot == true) {
		if (bullet->position.x >= 0 && bullet->position.x <= SWIDTH && bullet->position.y >= 0 && bullet->position.y <= SHEIGHT) {
			//Good
		} else {
			bulletReset();
		}
	}
}

void MyScene::bulletReset() {
	bullet->position = Point2(-1, -1);
	bullet->reset();
	playerSwitch();
	isAlive();
	playerShot = false;
}

// ###############################################################
// collision checks for collision between 2 objects
// ###############################################################
bool MyScene::collision(Entity* a, Entity* b)
{
	float eRadius = (a->sprite()->width() * a->scale.x) / 2;
	float aRadius = (b->sprite()->width() * b->scale.x) / 2;
	if (sqrt(pow(a->position.x - b->position.x, 2) + pow(a->position.y - b->position.y, 2)) <= eRadius + aRadius) {
		if (a == bullet && b == tank) {
			tank->damage(bullet->getDamage());
			std::cout << tank->getHealth() << std::endl;
		}
		if (a == bullet && b == tank2) {
			tank2->damage(bullet->getDamage());
			std::cout << tank2->getHealth() << std::endl;
		}
		return true;
	} else { 
		return false; 
	}
}

void MyScene::isAlive() {
	if (tank->getHealth() <= 0) {
		tank->position.x = -5;
		tank->position.y = -5;
		std::cout << "Player 2 won" << std::endl;
		player = 3;
	} else if(tank2->getHealth() <= 0) {
		tank2->position.x = -5;
		tank2->position.y = -5;
		std::cout << "Player 1 won" << std::endl;
		player = 3;
	} else {
		std::cout << "no one died yet" << std::endl;
	}
}
