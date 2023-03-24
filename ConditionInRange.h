#ifndef CONDITION_IN_RANGE_H
#define CONDITION_IN_RANGE_H
#include "Condition.h"
#include "VMath.h"
using namespace MATH;

class ConditionInRange : public Condition
{
public:
	ConditionInRange(Character* owner_) : Condition{ owner_ } 
	{
		//initialize any local variables here
	}

	bool test();
};

class ConditionOutOfRange : public Condition
{
public:
	ConditionOutOfRange(Character* owner_) : Condition{ owner_ }
	{
		//initialize any local variables here
	}

	bool test();
};

#endif;