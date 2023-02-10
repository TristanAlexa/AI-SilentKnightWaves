#include "StaticBody.h" 

void StaticBody::Update(float deltaTime, KinematicSteeringOutput* steering)
{
	//call the base class update, at the end or beginning
	Body::Update(deltaTime);
	//newOrientation(); //change where this is called


	// If there is no steering, set vel and rotation to null
	if (steering == NULL)
	{
		vel = Vec3();
		rotation = 0.0f;
		return;
	}
	// steering
	vel = steering->velocity;
	rotation = steering->rotation;

	// clip to maxValues
	if (VMath::mag(vel) > maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	}

	if (rotation > maxRotation)
	{
		rotation = maxRotation;
	}
}

void StaticBody::newOrientation()
{
	if (VMath::mag(vel) > 0.0f)
	{
		orientation = atan2(-vel.y, vel.x);
	}
}
