#include "Flee.h"

Flee::Flee(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
}

Flee::~Flee()
{
}

SteeringOutput* Flee::getSteering()
{
	// Get direction away from target
	result->linear = character->getPos() - target->getPos();

	// Accelerate in the above direction
	result->linear = VMath::normalize(result->linear) * character->getMaxAcceleration();
	result->angular = 0;

	return result;
}
