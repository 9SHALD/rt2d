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
	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH/2, SHEIGHT/2);
	tank = new MyTank();
	tank->position = Point2(SWIDTH / 1.5, SHEIGHT / 1.5);


	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(myentity);
	this->addChild(tank);
}


MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(myentity);
	this->removeChild(tank);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete myentity;
	delete tank;
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
	// Spacebar scales myentity
	// ###############################################################
	if (input()->getKeyDown(KeyCode::Space)) {
		myentity->scale = Point(0.2f, 0.2f);
		tank->scale = Point(0.2f, 0.2f);
	}
	if (input()->getKeyUp(KeyCode::Space)) {
		myentity->scale = Point(0.5f, 0.5f);
		tank->scale = Point(0.5f, 0.5f);
	}
	
	/*if (input()->getKeyDown(KeyCode::A)) {
		tank->scale -= Point(0.2f, 0.2f);
	}
	if (input()->getKeyDown(KeyCode::D)) {
		tank->scale += Point(0.2f, 0.2f);
	}*/

	// ###############################################################
	// Rotate color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		RGBAColor color = myentity->sprite()->color;
		myentity->sprite()->color = Color::rotate(color, 0.01f);
	}
	if (t.seconds() > 0.0333f) {
		RGBAColor color = tank->sprite()->color;
		tank->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}
}
