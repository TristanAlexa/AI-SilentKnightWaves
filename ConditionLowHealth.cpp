#include "ConditionLowHealth.h"
#include "Character.h"
bool ConditionLowHealth::test()
{
    int minimumHealth = 1;
    if (owner->getHealth() <= minimumHealth)
        return true;
    else
        return false;
}

bool ConditionHealthy::test()
{
    int maxHealth = 3;
    if (owner->getHealth() == maxHealth)
        return true;
    else
        return false;
}
