#ifndef ARRIVE_H
#define ARRIVE_H

#include "SteeringBehaviour.h"
class Arrive : public SteeringBehaviour {
protected:
	Body* target;

	float maxAccel;
	float maxSpeed;
	float targetRadius; //radius for arriving at the target
	float slowRadius;
	const float timeToTarget = 0.1f;


public:

	Arrive(Body* character_, Body* target_);
	~Arrive();
	SteeringOutput* getSteering();
};

#endif;