#ifndef FOLLOWAPATH_H
#define FOLLOWAPATH_H
#include "Arrive.h"
#include "Path.h"
#include "Body.h"
class FollowAPath : public Arrive
{
private:
	Path* path;
	vector <Node*> nodesToFollow;
	
public:
	FollowAPath(Body* character_, Body* target_, Path* path_);
	~FollowAPath();
	SteeringOutput* getSteering() override;
};

#endif;
