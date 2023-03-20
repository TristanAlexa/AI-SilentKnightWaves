#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"

enum class ACTION_SET {SEEK, ARRIVE, FOLLOWAPATH, DO_NOTHING}; //add more actions for the characters Arrive, follow path
class Action : public DecisionTreeNode
{
private:
	// set value to be one of the actions in the enum
	ACTION_SET value; 

public:
	Action(ACTION_SET value_)
	{
		value = value_;
	}
	~Action() {}

	// Returns the current action
	ACTION_SET getValue()
	{
		return value;
	}
	
	// Returns an action
	DecisionTreeNode* makeDecision()
	{
		return this;
	}
};
#endif
