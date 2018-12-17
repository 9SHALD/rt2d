#ifndef BULLET_H
#define BULLET_H

#include <rt2d/entity.h>

class MyBullet : public Entity
{
public:
	/// @brief Constructor
	MyBullet();
	/// @brief Destructor
	virtual ~MyBullet();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void move(float speed);
	void move(float degrees, float speed);

	void reset();
	
private:
	/* add your private declarations */
	Point2 _velocity;
	float _rotation;
};

#endif /* BULLET_H */


