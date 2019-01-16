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

private:
	/// 2 tanks and a floor
	MyTank* tank2;
	MyTank* tank;
	MyFloor* floor;
	MyBullet* bullet;

	int player;
	bool playerShot;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;

	Text* healthTxt1;
	Text* healthTxt2;
	Text* player1;
	Text* player2;

	std::stringstream healthT1;
	std::stringstream healthT2;
	std::stringstream player1Txt;
	std::stringstream player2Txt;
};

#endif /* SCENE00_H */
