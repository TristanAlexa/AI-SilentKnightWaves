#ifndef OBSTACLEAVOIDANCE_H
#define OBSTACLEAVOIDANCE_H
#include "Seek.h"
#include "Collider.h"
class ObstacleAvoidance : public Seek {

private:
	Collider* detector;
	float avoidDistance;  // min distance to a wall (should be > radius of character)
	float lookAhead;      // length of collision ray

public:
	ObstacleAvoidance();
	~ObstacleAvoidance();

	SteeringOutput* getSteering();
};
#endif;
