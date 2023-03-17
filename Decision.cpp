#include "Decision.h"

// Allows for more complex decisions in the readDecisionTree() in the character class
DecisionTreeNode* Decision::makeDecision()
{
    DecisionTreeNode* branch = getBranch();
    return branch->makeDecision();
}

bool Decision::testValue()
{
    // the sub classes will include the logic for the test value
    return false; 
}

DecisionTreeNode* Decision::getBranch()
{
    if (testValue())
        return trueNode;
    else
        return falseNode;
}
