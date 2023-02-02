#ifndef FLEE_H
#define FLEE_H
#include "SteeringBehaviour.h"

class Flee : public SteeringBehaviour
{
protected:
	Body* target;

public:
	Flee(Body* character_, Body* target_);
	virtual ~Flee();
	SteeringOutput* getSteering();
};

#endif;
