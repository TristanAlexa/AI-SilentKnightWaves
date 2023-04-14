#include "ConditionInRange.h"
#include "CharacterAdapter.h"

bool ConditionInRange::test()
{
    float thresholdDistance = 3.0f;

    if (VMath::distance(owner->getPlayerPos(), owner->getPos()) < thresholdDistance)
    {
        return true;
    }
    return false;
}

bool ConditionOutOfRange::test()
{
    float thresholdDistance = 3.5f;

    if (VMath::distance(owner->getPlayerPos(), owner->getPos()) > thresholdDistance)
    {
        return true;
    }
    return false;
}
