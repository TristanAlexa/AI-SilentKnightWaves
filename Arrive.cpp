#include "Arrive.h"

Arrive::Arrive(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	maxAccel = 5.0f;
	maxSpeed = 4.0f;
	slowRadius = 2.0f;
	targetRadius = 3.0f;
}

Arrive::~Arrive(){}

SteeringOutput* Arrive::getSteering()
{
	// Get direction to target
	Vec3 direction = target->getPos() - character->getPos();
	float distance = VMath::mag(direction);

	// Radius check for arriving 
	if (distance < targetRadius)
	{
		return NULL;
	}

	float targetSpeed;
	Vec3 targetVelocity;
	// Use max speed when outside the slow radius
	if (distance > slowRadius)
	{
		targetSpeed = maxSpeed;
	}
	else
	{
		targetSpeed = maxSpeed * distance / slowRadius;
	}

	// Calcuate velocity in the direction to target
	targetVelocity = direction;
	targetVelocity = VMath::normalize(targetVelocity);
	targetVelocity *= targetSpeed;
	
	// Acclerate, and slow down near the target
	result->linear = targetVelocity - character->getVel();
	result->linear /= timeToTarget;

	// Clip to max accel
	if (VMath::mag(result->linear) > maxAccel)
	{
		result->linear = VMath::normalize(result->linear);
		result->linear *= maxAccel;
	}

	result->angular = 0.0f;
	return result;

	return result;
}
