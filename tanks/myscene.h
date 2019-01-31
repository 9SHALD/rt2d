/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include <rt2d/text.h>

#include "tank.h"
#include "floor.h"
#include "barrel.h"
#include "bullet.h"



/// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	bool isGrounded(Entity* a, Entity* b);
	void playerMove();
	void playerSwitch();
	void bulletOnScreen();
	void nextTurn();
	bool collision(Entity* a, Entity* b);
	void isAlive();
	void reset();
	void updateHealth();
	void updateFuel();
	void updatePower(float a);

private:
	/// 2 players and a floor
	MyTank* player2;
	MyTank* player1;
	MyFloor* floor;
	MyBullet* bullet;

	int player;
	bool playerShot;
	float powerP1;
	float powerP2;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;

	Text* start;
	Text* healthP1;
	Text* healthP2;
	Text* playerTxt1;
	Text* playerTxt2;
	Text* fuelP1;
	Text* fuelP2;
	Text* power;

	std::stringstream healthT1;
	std::stringstream healthT2;
	std::stringstream fuelP1Txt;
	std::stringstream fuelP2Txt;
	std::stringstream powerTxt;
	
};

#endif /* SCENE00_H */
