#include "KinematicWander.h"

KinematicWander::KinematicWander(Body* character_)
{
	character = character_;
	maxSpeed = 3.0f;
	maxRotationSpeed = 2.0f;
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
	// result.vel = madSpeed * character.orientation.asVec3()
	result->velocity = maxSpeed * Vec3(character->getOrientation(), 1.0f, 1.0f);
	
	// result.rotation = random# * maxRotationspeed;
	result->rotation = RandomBinomial() * maxRotationSpeed;
	return result;
}

float KinematicWander::RandomBinomial()
{
	return Random() - Random();
}

float KinematicWander::Random()
{
	//return a random float from 0-1;
	return 0.0f;
}
