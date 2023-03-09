#include "FollowAPath.h"

FollowAPath::FollowAPath(Body* character_, Node* target_, Path* path_) : Arrive(character_,target), path(path_)
{
    path = new Path();
}

FollowAPath::~FollowAPath()
{
	delete path;
}

SteeringOutput* FollowAPath::getSteering()
{
    Vec3 target_position;

    if (!path) return nullptr;

    target_position = path->getCurrentNodePos();

    if (VMath::distance(character->getPos(), target_position) <= slowRadius)
    {
        path->incrementCurrentNode(1);
    }

    target->setPos(target_position);

    return Arrive::getSteering();
}