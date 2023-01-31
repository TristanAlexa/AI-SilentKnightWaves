#ifndef COLLIDER
#define COLLIDER
#include "Vector.h"
#include "VMath.h"
#include "Body.h"
#include "Plane.h"
class Collider

{
public:
	//Collision Detection Methods
	static bool SphereSphereCollisionDetected(const Body& body1, const Body& body2);

	static bool SpherePlaneCollisionDetected(const Body& body1, const Plane& plane);

	//Collsion repsonse Methods
	static void SphereSphereCollisionResponse(Body& body1, Body& body2, float elasticity);

	static void SphereStaticSphereCollisionRepsonse(Body& body1, const Body& staticSphere);

	static void SpherePlaneCollisionResponse(Body& body1, const Plane& plane);

};
#endif

