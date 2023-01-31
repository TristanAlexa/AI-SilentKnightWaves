#include "ObstacleAvoidance.h"

ObstacleAvoidance::ObstacleAvoidance() : Seek(character, target) {
	avoidDistance = 4.0f;
	detector = new Collider;
	lookAhead = 1.0f;
}

ObstacleAvoidance::~ObstacleAvoidance()
{
	if (detector)
	{
		delete detector;
	}
}

SteeringOutput* ObstacleAvoidance::getSteering()
{
	// 1. Calculate the collision ray vector
	Vec3 ray = VMath::normalize(character->getVel());
	ray *= lookAhead;
	return nullptr;

	// find the collision
	// use method from physics.main

	//if no collision 
		//return null

	// 2. Else create a target and delegate to seek
}
