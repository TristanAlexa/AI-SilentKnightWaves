#ifndef PLAYER_IN_RANGE_DECISION_H
#define PLAYER_IN_RANGE_DECISION_H


#include "Decision.h"
#include "VMath.h"
#include "Character.h"

class Character;

using namespace MATH;
class PlayerInRangeDecision :public Decision
{
protected:
	Character* owner;
public:
	PlayerInRangeDecision(DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_, Character* owner_)
	{
		trueNode = trueNode_;
		falseNode = falseNode_;
		owner = owner_;
	}

	bool testValue();
};
#endif;

