#ifndef PLANE
#define PLANE
#include "Vector.h"
#include "VMath.h"
#include "Body.h"

class Plane : public Vec4
{
public:
	Vec4 plane;
	//4D plane constructers
	Plane();

	~Plane();
	Plane(float x_, float y_, float z_, float d_);
	Plane(Vec3 normal_, float d_);
	//Defines plane from three points on the plane
	Plane(const Vec3& v0, const Vec3& v1, const Vec3& v2);
	//Finds the distance between a sphere shaped body and the plane
	float distance(const Body& body);

};
#endif


