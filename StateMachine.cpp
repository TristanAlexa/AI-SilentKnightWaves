#include "StateMachine.h"

//STATEMACHINE cpp
void StateMachine::update()
{
	Transition* triggered = NULL;
	for (Transition* t : currentState->getTransitions())
	{
		if (t->isTriggered())
		{
			triggered = t;
			break;
		}
	}
	if (triggered)
	{
		currentState = triggered->getTargetState();
		return;
	}
	else
		return;
}

STATE StateMachine::getCurrentStateName()
{
	return currentState->getName();
}

void StateMachine::setInitialState(State* initial_)
{
	initialState = initial_;
	currentState = initialState;
}

//STATE class
State::State(STATE name_)
{
	name = name_;
}

list<Transition*> State::getTransitions()
{
	return transitions;
}

void State::addTransition(Transition* transition_)
{
	transitions.push_back(transition_);
}

STATE State::getName()
{
	return name;
}

Transition::Transition(Condition* condition_, State* targetState_)
{
	condition = condition_;
	targetState = targetState_;
}

Transition::~Transition()
{
}
