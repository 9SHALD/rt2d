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
	tank->position = Point2(SWIDTH / 2, SHEIGHT / 1.5);
	tank2 = new MyTank();
	tank2->position = Point2(SWIDTH / 1.5, SHEIGHT / 1.5);
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
	player = 1;
	playerShot = 0;


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
	
	// ###############################################################
	// checks if player is grounded and if player is grounded lets them move
	// ###############################################################
	switch (player) {
	case 1:
		if (isGrounded(tank, floor)) {
			tank->movement();
			if (input()->getKeyDown(KeyCode::Space) ){
				bullet->position = tank->position;
				bullet->rotation.z = tank->barrelrot;
				bullet->move(5);
			}
		}
		if (collition(bullet, tank2)) {
			bullet->position = Point2(-1, -1);
			bullet->reset();
		}
		break;
	case 2:
		if (isGrounded(tank2, floor)) {
			tank2->movement();
			if (input()->getKeyDown(KeyCode::Space) ){
				bullet->position = tank2->position;
				bullet->rotation.z = tank2->barrelrot;
				bullet->move(5);
			}
		}
		if (collition(bullet, tank)) {
			bullet->position = Point2(-1, -1);
			bullet->reset();
		}
		break;
	}

	if (isGrounded(bullet, floor)) {
		bullet->position = Point2(-1, -1);
		bullet->reset();
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
	resetBullet();
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
void MyScene::playerTurn()
{
	if (player == 1) {
		player = 2;
	}
	if (player == 2) {
		player = 1;
	}
}

void MyScene::resetBullet()
{
	if (bullet->position.x <= 0 || bullet->position.x >= SWIDTH) {
		bullet->position = Point2(-1, -1);
		bullet->reset();
	}
}

bool MyScene::collition(Entity* c, Entity* d)
{
	float eRadius = (c->sprite()->width() * c->scale.x) / 2;
	float aRadius = (d->sprite()->width() * d->scale.x) / 2;
	if (sqrt(pow(c->position.x - d->position.x, 2) + pow(c->position.y - d->position.y, 2)) <= eRadius + aRadius) {
		std::cout << "Hit" << std::endl;
		return true;
	} else { 
		return false; 
	}
}