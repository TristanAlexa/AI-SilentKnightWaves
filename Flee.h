#ifndef FLEE_H
#define FLEE_H
#include "SteeringBehaviour.h"

// Flee will be used as part of the AI decision making process.
// AI's will Flee from the character when in a certain range or after being attacked
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
