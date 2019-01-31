/*				*
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>

#include "myscene.h"

MyScene::MyScene() : Scene() {
	// start the timer.
	t.start();

	// create a single instance of all entities on the screen.
	player1 = new MyTank();
	player1->position = Point2(SWIDTH / 4, SHEIGHT / 1.3);
	player2 = new MyTank();
	player2->position = Point2(SWIDTH / 4 * 3, SHEIGHT / 1.3);
	floor = new MyFloor();
	floor->position = Point2(SWIDTH / 2, SHEIGHT / 1.2);
	bullet = new MyBullet();
	bullet->position = Point2(-1, -1);
	bullet->sprite()->color = WHITE;

	player = 4;
	playerShot = false;
	powerP1 = 5;
	powerP2 = 5;

	
	healthT1 << "Health: " << player1->getHealth();
	healthT2 << "Health: " << player2->getHealth();
	fuelP1Txt << "Fuel  : " << player1->getFuel();
	fuelP2Txt << "Fuel  : " << player2->getFuel();
	powerTxt << "Power: " << powerP1;
	
	start = new Text();
	start->message("Press Space to start");
	start->position = Point2((SWIDTH / 2) - 240, SHEIGHT / 2);

	healthP1 = new Text();
	healthP1->position = Point2(35, 55);
	healthP1->message(healthT1.str());
	healthP1->scale = Point(0.5f, 0.5f);
	healthP2 = new Text();
	healthP2->position = Point2(SWIDTH - 190, 55);
	healthP2->message(healthT2.str());
	healthP2->scale = Point(0.5f, 0.5f);

	playerTxt1 = new Text();
	playerTxt1->position = Point2(35, 30);
	playerTxt1->message("Player 1", RED);
	playerTxt1->scale = Point(0.5f, 0.5f);
	playerTxt2 = new Text();
	playerTxt2->position = Point2(SWIDTH - 190, 30);
	playerTxt2->message("Player 2", CYAN);
	playerTxt2->scale = Point(0.5f, 0.5f);

	fuelP1 = new Text();
	fuelP1->position = Point2(35, 75);
	fuelP1->message(fuelP1Txt.str());
	fuelP1->scale = Point(0.5f, 0.5f);
	fuelP2 = new Text();
	fuelP2->position = Point2(SWIDTH - 190, 75);
	fuelP2->message(fuelP2Txt.str());
	fuelP2->scale = Point(0.5f, 0.5f);

	power = new Text();
	power->position = Point2(SWIDTH / 2 - 20, 75);
	power->message(powerTxt.str());
	power->scale = Point(0.5f, 0.5f);

	
	// sets the scale of all objects
	player1->scale = Point(0.2f, 0.2f);
	player2->scale = Point(0.2f, 0.2f);
	floor->scale = Point((SWIDTH / 2), 0.2f);
	bullet->scale = Point2(0.1f, 0.1f);
	player2->setBarrelRot(-PI);

	player1->sprite()->color = RED;
	player2->sprite()->color = CYAN;


	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(player1);
	this->addChild(player2);
	this->addChild(floor);
	this->addChild(bullet);
	this->addChild(healthP1);
	this->addChild(healthP2);
	this->addChild(playerTxt1);
	this->addChild(playerTxt2);
	this->addChild(fuelP1);
	this->addChild(fuelP2);
	this->addChild(power);
	this->addChild(start);

}


MyScene::~MyScene() {
	// deconstruct and delete the Tree
	this->removeChild(player1);
	this->removeChild(player2);
	this->removeChild(floor);
	this->removeChild(bullet);
	this->removeChild(healthP1);
	this->removeChild(healthP2);
	this->removeChild(playerTxt1);
	this->removeChild(playerTxt2);
	this->removeChild(fuelP1);
	this->removeChild(fuelP2);
	this->removeChild(power);
	this->removeChild(start);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete player1;
	delete player2;
	delete floor;
	delete bullet;
	delete healthP1;
	delete healthP2;
	delete playerTxt1;
	delete playerTxt2;
	delete fuelP1;
	delete fuelP2;
	delete power;
	delete start;
}

void MyScene::update(float deltaTime) {

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
	if (!isGrounded(player1, floor)) {
		player1->gravity();	
	}
	if (!isGrounded(player2, floor)) {
		player2->gravity();
	}
	bulletOnScreen();
}


// ###############################################################
// isGrounded checks if a object is hitting the floor/ground
// ###############################################################
bool MyScene::isGrounded(Entity* a, Entity* b) {
	int aPos = a->position.y + (a->sprite()->height() * a->scale.y) / 2;
	int bPos = b->position.y - (b->sprite()->height() * b->scale.y) / 2;
	if (aPos > bPos) {
		return true;
	} else {
		return false;
	}
}


// ###############################################################
// changes wich players turn it is
// ###############################################################
void MyScene::playerMove() {
	switch (player) {
	case 1:
		if (isGrounded(player1, floor)) {
			if (playerShot == false) {
				player1->movement();
				if (input()->getKey(KeyCode::A) || input()->getKey(KeyCode::D)) {
					updateFuel();
				}
				if (powerP1 > 2.1 && input()->getKey(KeyCode::Z)){
					powerP1 -= 0.1;
					updatePower(powerP1);
				}
				if (powerP1 < 10 && input()->getKey(KeyCode::X)) {
					powerP1 += 0.1;
					updatePower(powerP1);
				}
				if (input()->getKeyDown(KeyCode::Space)) {
					bullet->position = player1->position;
					bullet->rotation.z = player1->barrelrot;
					bullet->move(powerP1);
					playerShot = true;
				}
			}
		}
		if (collision(bullet, player2)) {
			nextTurn();
		}
		break;
	case 2:
		if (isGrounded(player2, floor)) {
			if (playerShot == false) {
				player2->movement();
				if (input()->getKey(KeyCode::A) || input()->getKey(KeyCode::D)) {
					updateFuel();
				}
				if (powerP2 > 2.1 && input()->getKey(KeyCode::Z)) {
					powerP2 -= 0.1;
					updatePower(powerP2);
				}
				if (powerP2 < 10 && input()->getKey(KeyCode::X)) {
					powerP2 += 0.1;
					updatePower(powerP2);
				}
				if (input()->getKeyDown(KeyCode::Space)) {
					bullet->position = player2->position;
					bullet->rotation.z = player2->barrelrot;
					bullet->move(powerP2);
					playerShot = true;
				}
			}
		}
		if (collision(bullet, player1)) {
			nextTurn();
		}
		break;
	case 3:
		for (int i = 0; i < 60; i++) {
			if (i == 30) {
				if (player1->getHealth() <= 0) {
					start->message("Player 2 Won!");
					start->position = Point2((SWIDTH / 2) - (start->message().size() * 64 / 2), SHEIGHT / 2);
				}
				if (player2->getHealth() <= 0) {
					start->message("Player 1 Won!");
					start->position = Point2((SWIDTH / 2) - (start->message().size() * 64 / 2), SHEIGHT / 2);
				}
			}
			if (i == 0) {
				start->message("Use R to restart");
			}
		}
		if (input()->getKeyDown(KeyCode::R)) {
			start->message("");
			reset();
		}
		break;
	case 4:
		if (input()->getKeyDown(KeyCode::Space)) {
			start->message("");
			player = 1;
		}
		break;
	}
}

void MyScene::playerSwitch() {
	if (player == 1) {
		player = 2;
		updatePower(powerP2);
	} else if (player == 2) {
		player = 1;
		updatePower(powerP1);
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
	player1->setFuel(500);
	player2->setFuel(500);
	playerShot = false;
}

// ###############################################################
// collision checks for collision between 2 objects
// ###############################################################
bool MyScene::collision(Entity* a, Entity* b) {
	float eRadius = (a->sprite()->width() * a->scale.x) / 2;
	float aRadius = (b->sprite()->width() * b->scale.x) / 2;
	if (sqrt(pow(a->position.x - b->position.x, 2) + pow(a->position.y - b->position.y, 2)) <= eRadius + aRadius) {
		if (a == bullet && b == player1) {
			player1->damage(bullet->getDamage());
			std::cout << player1->getHealth() << std::endl;
		}
		if (a == bullet && b == player2) {
			player2->damage(bullet->getDamage());
			std::cout << player2->getHealth() << std::endl;
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
	if (player1->getHealth() <= 0) {
		player1->position.x = -20;
		player1->position.y = -20;
		std::cout << "Player 2 won" << std::endl;
		player = 3;
	} else if(player2->getHealth() <= 0) {
		player2->position.x = -20;
		player2->position.y = -20;
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
	player1->position = Point2(SWIDTH / 4, SHEIGHT / 1.5);
	player2->position = Point2(SWIDTH / 4 * 3, SHEIGHT / 1.5);
	player1->setBarrelRot(0);
	player2->setBarrelRot(-PI);
	player1->setHealth(100);
	player2->setHealth(100);
	player1->setFuel(500);
	player2->setFuel(500);
	powerP1 = 5;
	powerP2 = 5;
	updateHealth();
	updateFuel();
	updatePower(powerP1);
	player = 1;
}

void MyScene::updateHealth() {	
	healthT1.str(std::string());
	healthT2.str(std::string());
	healthT1 << "Health: " << player1->getHealth();
	healthT2 << "Health: " << player2->getHealth();
	healthP1->message(healthT1.str());
	healthP2->message(healthT2.str());
}

void MyScene::updateFuel() {
	fuelP1Txt.str(std::string());
	fuelP2Txt.str(std::string());
	fuelP1Txt << "Fuel  : " << player1->getFuel();
	fuelP2Txt << "Fuel  : " << player2->getFuel();
	fuelP1->message(fuelP1Txt.str());
	fuelP2->message(fuelP2Txt.str());
}

void MyScene::updatePower(float a) {
	powerTxt.str(std::string());
	powerTxt << "Power: " << a;
	power->message(powerTxt.str());
}
