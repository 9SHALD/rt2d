/*				*
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>

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


	healthT1 << "Health: " << tank->getHealth();
	healthT2 << "Health: " << tank2->getHealth();
	player1Txt << "Player 1";
	player2Txt << "Player 2";

	healthTxt1 = new Text();
	healthTxt1->position = Point2(35, 55);
	healthTxt1->message(healthT1.str());
	healthTxt1->scale = Point(0.5f, 0.5f);
	healthTxt2 = new Text();
	healthTxt2->position = Point2(SWIDTH - 190, 55);
	healthTxt2->message(healthT2.str());
	healthTxt2->scale = Point(0.5f, 0.5f);

	player1 = new Text();
	player1->position = Point2(35, 30);
	player1->message(player1Txt.str(), RED);
	player1->scale = Point(0.5f, 0.5f);
	player2 = new Text();
	player2->position = Point2(SWIDTH - 190, 30);
	player2->message(player2Txt.str(), CYAN);
	player2->scale = Point(0.5f, 0.5f);
	
	// sets the scale of all objects
	tank->scale = Point(0.2f, 0.2f);
	tank2->scale = Point(0.2f, 0.2f);
	floor->scale = Point((SWIDTH / 2), 0.2f);
	bullet->scale = Point2(0.1f, 0.1f);
	tank2->setBarrelRot(-PI);
	player = 1;
	playerShot = false;

	tank->sprite()->color = RED;
	tank2->sprite()->color = CYAN;


	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(tank);
	this->addChild(tank2);
	this->addChild(floor);
	this->addChild(bullet);
	this->addChild(healthTxt1);
	this->addChild(healthTxt2);
	this->addChild(player1);
	this->addChild(player2);

}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(tank);
	this->removeChild(tank2);
	this->removeChild(floor);
	this->removeChild(bullet);
	this->removeChild(healthTxt1);
	this->removeChild(healthTxt2);
	this->removeChild(player1);
	this->removeChild(player2);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete tank;
	delete tank2;
	delete floor;
	delete bullet;
	delete healthTxt1;
	delete healthTxt2;
	delete player1;
	delete player2;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// calls the player movement script
	// ###############################################################
	playerMove();

	// ###############################################################
	// checks if the bullet hits the ground;
	// ###############################################################
	if (isGrounded(bullet, floor)) {
		nextTurn();
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
			nextTurn();
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
			nextTurn();
		}
		break;
	case 3:
		if (input()->getKeyDown(KeyCode::R)) {
			reset();
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
			nextTurn();
		}
	}
}

void MyScene::nextTurn() {
	bullet->position = Point2(-1, -1);
	bullet->reset();
	updateHealth();
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

// ###############################################################
// checks if the tanks(players) are alive
// ###############################################################
void MyScene::isAlive() {
	if (tank->getHealth() <= 0) {
		tank->position.x = -20;
		tank->position.y = -20;
		std::cout << "Player 2 won" << std::endl;
		player = 3;
	} else if(tank2->getHealth() <= 0) {
		tank2->position.x = -20;
		tank2->position.y = -20;
		std::cout << "Player 1 won" << std::endl;
		player = 3;
	} else {
		std::cout << "no one died yet" << std::endl;
	}
}

// ###############################################################
// resets the game back to the starting position
// ###############################################################
void MyScene::reset() {
	tank->position = Point2(SWIDTH / 4, SHEIGHT / 1.5);
	tank2->position = Point2(SWIDTH / 4 * 3, SHEIGHT / 1.5);
	tank->setBarrelRot(0);
	tank2->setBarrelRot(-PI);
	tank->setHealth(100);
	tank2->setHealth(100);
	player = 1;
}

void MyScene::updateHealth()
{	
	healthT1.str(std::string());
	healthT2.str(std::string());
	healthT1 << "Health: " << tank->getHealth();
	healthT2 << "Health: " << tank2->getHealth();
	healthTxt1->message(healthT1.str());
	healthTxt2->message(healthT2.str());
}
