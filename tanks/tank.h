#ifndef TANK_H
#define TANK_H

#include <rt2d/entity.h>

#include "barrel.h"

class MyTank : public Entity
{
public:
	/// @brief Constructor
	MyTank();
	/// @brief Destructor
	virtual ~MyTank();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void movement();

	void gravity();
	void setBarrelRot(float a);
	
	float barrelrot;

private:

	/* add your private declarations */
	MyBarrel* barrel;

	int shot;
};

#endif /* TANK_H */