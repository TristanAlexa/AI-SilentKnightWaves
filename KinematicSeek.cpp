#include "KinematicSeek.h"

KinematicSeek::KinematicSeek(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput;
}

KinematicSeek::~KinematicSeek()
{
	if (result)
	{
		delete result;
	}
}

KinematicSteeringOutput* KinematicSeek::getSteering()
{
	// 1. Find Resultant velocity
	result->velocity = target->getPos() - character->getPos();

	// 2. Normalize vel and multiply by max speed (go full speed in this direciton)
	result->velocity = VMath::normalize(result->velocity) * character->getMaxSpeed();


	// 3. find rotation {character.orientation = newOrientation(character.orientation, result->velocity)
	result->rotation = 0.0f;
	return result;
}
