#ifndef KINEMATICSEEK_H
#define KINEMATICSEEK_H

#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include "KinematicSteeringOutput.h"

using namespace MATH;

class KinematicSeek
{
private:
	KinematicSteeringOutput* result;
	Body* character;
	Body* target;

public:
	KinematicSeek(Body* character_, Body* target_);
	~KinematicSeek();
	KinematicSteeringOutput* getSteering();
};

#endif // !KINEMATICSEEK_H