#ifndef CONDITION_IN_JAIL_H
#define CONDITION_IN_JAIL_H
#include "Condition.h"
#include "VMath.h"

using namespace MATH;
class ConditionInJail : public Condition
{
public:
	ConditionInJail(CharacterAdapter* owner_) : Condition{ owner_ }{}
	bool test();
};

#endif;