#ifndef FOLLOWAPATH_H
#define FOLLOWAPATH_H
#include "Arrive.h"
#include "Path.h"
class FollowAPath : public Arrive
{
private:
	Path* path;
	
public:
	FollowAPath(Body* character_, Node* target_, Path* path_);
	~FollowAPath();
	SteeringOutput* getSteering() override;
};

#endif;
