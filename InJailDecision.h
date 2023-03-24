#ifndef IN_JAIL_DECISION_H
#define IN_JAIL_DECISION_H
#include "Decision.h"
#include "VMath.h"
#include "Character.h"


class Character;
using namespace MATH;

class InJailDecision : public Decision
{
protected:
	Character* owner;
	
	
public:
	InJailDecision(DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_, Character* owner_)
	{
		trueNode = trueNode_;
		falseNode = falseNode_;
		owner = owner_;
	}

	bool testValue();
};
#endif;
