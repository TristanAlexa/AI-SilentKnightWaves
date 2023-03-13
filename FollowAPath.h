#ifndef FOLLOWAPATH_H
#define FOLLOWAPATH_H
#include "Arrive.h"
#include "Path.h"
#include "Body.h"
class FollowAPath : public Arrive
{
private:
	Path* path;
public:
	FollowAPath(Body* character_, Body* target_, Path* path_);
	~FollowAPath() {}

	// Overrides the Arrive getSteering function to arrive at a series of nodes in a path
	SteeringOutput* getSteering() override;

};

#endif;
