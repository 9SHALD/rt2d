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

	bool isGrounded(int posY);
	void playerTurn();
	void resetBullet();

	void bulletHit();

private:
	/// 2 tanks and a floor
	MyTank* tank2;
	MyTank* tank;
	MyFloor* floor;
	MyBullet* bullet;

	int player;

	/// @brief a Timer to rotate the color every n seconds
	Timer t;
};

#endif /* SCENE00_H */
