#ifndef TANK_H
#define TANK_H

#include <rt2d/entity.h>

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

private:
	/* add your private declarations */
};

#endif /* TANK_H */