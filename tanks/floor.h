#ifndef FLOOR_H
#define FLOOR_H

#include <rt2d/entity.h>


class MyFloor : public Entity
{
public:
	/// @brief Constructor
	MyFloor();
	/// @brief Destructor
	virtual ~MyFloor();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* FLOOR_H */