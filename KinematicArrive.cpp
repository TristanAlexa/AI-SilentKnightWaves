#include "KinematicArrive.h"

KinematicArrive::KinematicArrive(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput;
	maxSpeed = 2.0f;
	radius = 2.0f;
}

KinematicArrive::~KinematicArrive()
{
	if (result)
	{
		delete result;
	}
}

KinematicSteeringOutput* KinematicArrive::getSteering()
{
	
	// 1. Find resultant velocity (gets direction to target)
	result->velocity = target->getPos() - character->getPos();

	// 2. Return Null if result.velocity.length() < radius
	float magOfResultantVel = VMath::mag(result->velocity);
	if (magOfResultantVel < radius) {
		return NULL;
	}

	// 3. Slow down near the target
	result->velocity /= timeToTarget; 

	// 4. Clip to max speed
	if (magOfResultantVel > maxSpeed) {
		result->velocity = VMath::normalize(result->velocity);
		result->velocity *= maxSpeed;
	}
	// 5. Set orientation and rotation
	result->rotation = 0.0f;
	return result;
}
