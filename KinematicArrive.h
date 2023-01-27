#ifndef KINEMATICARRIVE_H
#define KINEMATICARRIVE_H

#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include "KinematicSteeringOutput.h"

using namespace MATH;

class KinematicArrive
{
private:
	KinematicSteeringOutput* result;
	Body* character;
	Body* target;
	
	float maxSpeed;
	float radius; //satisfaction radius
	const float timeToTarget = 0.25f;


public: 
	KinematicArrive(Body* character_, Body* target_);
	~KinematicArrive();
	KinematicSteeringOutput* getSteering();

};

#endif
