/**
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

	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	tank = new MyTank();
	tank->position = Point2(SWIDTH / 2, SHEIGHT / 1.5);
	tank2 = new MyTank();
	tank2->position = Point2(SWIDTH / 1.5, SHEIGHT / 1.5);
	floor = new MyFloor();
	floor->position = Point2(SWIDTH / 2, SHEIGHT / 1.2);
	//sets the scale of the tanks and floor
	tank->scale = Point(0.2f, 0.2f);
	tank2->scale = Point(0.2f, 0.2f);
	floor->scale = Point((SWIDTH / 2), 0.2f);
	player = 1;


	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(tank);
	this->addChild(tank2);
	this->addChild(floor);
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
	// Left and Right movement
	// ###############################################################
	switch (player) {
	case 1:
		if (isGrounded(tank->position.y + (tank->sprite()->height() * tank->scale.y)) == 0) {
			tank->movement();
		}
		
		if (input()->getKeyDown(KeyCode::Space) ){
			player = 2;
		}
		break;
	case 2:
		if (isGrounded(tank2->position.y + (tank2->sprite()->height() * tank2->scale.y)) == 0) {
			tank2->movement();
		}
		if (input()->getKeyDown(KeyCode::Space) ){
			player = 1;
		}
		break;
	}
	
	// ###############################################################
	// if not grounded adds gravity
	// ###############################################################
	if (isGrounded(tank->position.y + (tank->sprite()->height() * tank->scale.y)) == 1) {
		tank->gravity();	
	}
	if (isGrounded(tank2->position.y + (tank2->sprite()->height() * tank2->scale.y)) == 1) {
		tank2->gravity();
	}

	// ###############################################################
	// Rotate color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		RGBAColor color = tank->sprite()->color;
		tank->sprite()->color = Color::rotate(color, 0.01f);
	}
	if (t.seconds() > 0.0333f) {
		RGBAColor color = tank2->sprite()->color;
		tank2->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}
}


// ###############################################################
// isGrounded checks if a object is hitting the floor
// ###############################################################
bool MyScene::isGrounded(int posY)
{
	if ((posY) < (floor->position.y)) {
		return true;
	}
	else {
		return false;
	}
}
