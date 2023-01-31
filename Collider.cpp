#include "Collider.h"
using namespace std;
using namespace MATH;

bool Collider::SphereSphereCollisionDetected(const Body& body1, const Body& body2) {
    //If the distance between the two spheres is smaller than the spheres radius then a collision has been detected
    Body tempBody1;
    Body tempBody2;
    float distanceBetweenSphereOrigins = VMath::distance(tempBody1.getPos(), tempBody2.getPos());
    if (distanceBetweenSphereOrigins < tempBody1.getRadius() + tempBody2.getRadius()) {
        return true;
    }
    return false;
}

bool Collider::SpherePlaneCollisionDetected(const Body& body1, const Plane& plane) {
    //If Plane::distance -> (N.S + D) is smaller than the sphere radius then a collision has been detected
    //If the distance is equal then the sphere is tangent to the plane
    Body tempBody;
    Plane plane1;
    float distanceFromPlane = plane1.distance(tempBody);
    if (distanceFromPlane <= (tempBody.getRadius())) {
        return true;
    }
    return false;
}

void Collider::SphereSphereCollisionResponse(Body& body1, Body& body2, float elasticity) {

    //find normal
    Vec3 n = body1.getPos() - body2.getPos();

    //normalize normal
    Vec3 normalizedn = VMath::normalize(n);

    //find initial velocities in the direction of the normal
    float v1in = VMath::dot(body1.getVel(), normalizedn);
    float v2in = VMath::dot(body2.getVel(), normalizedn);

    //find final velocity and include elasticity
    float v2fn = v1in * (1.0f + elasticity) / 2.0f;
    float v1fn = v1in - v2fn;


    float deltav1n = v1fn - v1in;
    float deltav2n = v2fn - v2in;
    body1.setVel(body1.getVel() + (deltav1n * normalizedn));
    body2.setVel(body2.getVel() + (deltav2n * normalizedn));

}

void Collider::SphereStaticSphereCollisionRepsonse(Body& body1, const Body& staticSphere) {
    Body tempBody2 = staticSphere;

    //normal vector
    Vec3 n = body1.getPos() - tempBody2.getPos();

    //normalized normal vector
    Vec3 normalizedn = VMath::normalize(n);

    //projection vector
    Vec3 negVel = -body1.getVel();
    Vec3 projVec = (VMath::dot(negVel, normalizedn)) * normalizedn;

    //Final velocity
    body1.setVel(body1.getVel() + (projVec * 2.0f));
}

void Collider::SpherePlaneCollisionResponse(Body& body1, const Plane& plane) {


    //find normal
    Vec3 normal;
    normal.x = plane.x;
    normal.y = plane.y;
    normal.z = plane.z;

    //normalized normal vector
    Vec3 normalizedNorm = VMath::normalize(normal);

    //proj vector
    Vec3 projectionVec = VMath::dot(-body1.getVel(), normalizedNorm) * normalizedNorm;

    //final vel
    body1.setVel(body1.getVel() + projectionVec * 2.0f);

}
