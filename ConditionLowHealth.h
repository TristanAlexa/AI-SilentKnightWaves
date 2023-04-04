#ifndef CONDITION_LOW_HEALTH_H
#define CONDITION_LOW_HEALTH_H
#include "Condition.h"
class ConditionLowHealth : public Condition
{
public:
	ConditionLowHealth(Character* owner_) : Condition{ owner_ } {}
	bool test();
};

class ConditionHealthy : public Condition
{
public:
	ConditionHealthy(Character* owner_) : Condition{ owner_ } {}
	bool test();
};
#endif;
