#ifndef KINEMATICWANDER_H
#define KINEMATICWANDER_H
#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include <time.h>
#include "KinematicSteeringOutput.h"
using namespace MATH;

class KinematicWander {
private:
	KinematicSteeringOutput* result;
	Body* character;
	float maxSpeed;
	float maxRotationSpeed;

public:
	KinematicWander(Body* character_);
	~KinematicWander();
	KinematicSteeringOutput* getSteering();

	// Returns a float from -1.0 to 1.0
	float RandomBinomial();
	// Returns a float from 0.0 - 1.0  
	float Random(); 

};
#endif;
