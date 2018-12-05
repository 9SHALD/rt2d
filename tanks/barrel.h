#ifndef BARREL_H
#define BARREL_H

#include <rt2d/entity.h>

class MyBarrel : public Entity
{
public:
	/// @brief Constructor
	MyBarrel();
	/// @brief Destructor
	virtual ~MyBarrel();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* BARREL_H */