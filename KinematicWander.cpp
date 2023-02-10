#include "KinematicWander.h"

KinematicWander::KinematicWander(Body* character_)
{
	character = character_;
	maxSpeed = 2.0f;
	maxRotationSpeed = 4.0f;
	result = new KinematicSteeringOutput;
}

KinematicWander::~KinematicWander()
{
	if (result)
	{
		delete result;
	}
}

KinematicSteeringOutput* KinematicWander::getSteering()
{
	// result.vel = maxSpeed * character.orientation.asVec3()
	result->velocity = maxSpeed * Vec3(cos(character->getOrientation()), sin(character->getOrientation()), 0.0f);
	
	// result.rotation = random# * maxRotationspeed;
	result->rotation = RandomBinomial() * maxRotationSpeed;
	return result;
}

float KinematicWander::RandomBinomial()
{
	float rb = Random() - Random();
	return rb;
}

float KinematicWander::Random()
{
	float randomFloat = (float) rand() / RAND_MAX;
	return randomFloat;
}
