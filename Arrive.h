#ifndef ARRIVE_H
#define ARRIVE_H
#include "SteeringBehaviour.h"

// Arrive used for the more difficult AI enemies. These enemies will arrive at a target to attack and destroy a target
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