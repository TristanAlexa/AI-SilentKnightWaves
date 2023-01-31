#include "Plane.h"

Plane::Plane()
{

}

Plane::~Plane()
{
}

Plane::Plane(float x_, float y_, float z_, float d_)
{
	x = x_;
	y = y_;
	z = z_;
	w = d_;
}

Plane::Plane(Vec3 normal_, float d_)
{
	x = normal_.x;
	y = normal_.y;
	z = normal_.z;
	w = d_;
}

Plane::Plane(const Vec3& v0, const Vec3& v1, const Vec3& v2) {
	//Temp variables for 3 points on a plane
	Vec3 vOne = v0;
	Vec3 vTwo = v1;
	Vec3 vThree = v2;
	//Two vectors made from 3 points
	Vec3 e1 = vTwo - vOne;
	Vec3 e2 = vThree - vOne;

	//	1. Find normal by using cross product on the vectors
	Vec3 normal = VMath::cross(e1, e2);
	//	2. Normalize the normal of plane
	Vec3 normalized = VMath::normalize(normal);
	//	3. Solve for D, pick any point and extend to 4D -> (v0, v1, v2, w=1) : dot product of normalized normal of plane and any point given
	float result = VMath::dot(normalized, v0);
	float D = -result;
	//	4. Construct Plane(Vec3 normal_, float d_)
	x = normalized.x;
	y = normalized.y;
	z = normalized.z;
	w = D;
}

float Plane::distance(const Body& body)
{
	Body tempBody = body;
	Vec3 planeNormal(plane.x, plane.y, plane.z);
	//distance to plane
	float distance = VMath::dot(planeNormal, tempBody.getPos()) + plane.w - tempBody.getRadius();
	return distance;

}
