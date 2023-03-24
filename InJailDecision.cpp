#include "InJailDecision.h"

bool InJailDecision::testValue()
{
    float minDistance = 0.5f;

    // Hard coded values of jail tile positions to avoid circular dependency
    Vec3 jail1Pos = Vec3(1.05f, 0.95f, 0.0f);
    Vec3 jail2Pos = Vec3(24.15f, 0.95f, 0.0f);
    Vec3 jail3Pos = Vec3(1.05f, 14.25f, 0.0f);
    Vec3 jail4Pos = Vec3(24.15f, 14.25f, 0.0f);

    // Return true when the character is within the minimum distance of any jail tile position
    if (VMath::distance(owner->getPos(), jail1Pos) < minDistance)
    {
        return true;
    }
    else if(VMath::distance(owner->getPos(), jail2Pos) < minDistance)
    {
        return true;
    }
    else if (VMath::distance(owner->getPos(), jail3Pos) < minDistance)
    {
        return true;
    }
    else if (VMath::distance(owner->getPos(), jail4Pos) < minDistance)
    {
        return true;
    }
    //If not within range, return the branch/ test values for the player in range decision
    return false;
    
    
}
