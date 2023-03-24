#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <list>
#include "Condition.h"

class Transition;
using namespace std;

enum class STATE { SEEK, ARRIVE, FOLLOWAPATH, DO_NOTHING };

class State
{
private:
	list<Transition*> transitions;
	STATE name;//values of the enum

public:
	State(STATE name_);
	~State() {}
	list<Transition*> getTransitions();
	void addTransition(Transition* transition_);
	STATE getName();
};

class Transition
{
private:
	Condition* condition;
	State* targetState;

public:
	Transition(Condition* condition_, State* targetState_);
	~Transition();

	bool isTriggered() { return condition->test(); }
	State* getTargetState() { return targetState; }
};

class StateMachine
{
private:
	State* initialState;
	State* currentState;

public:
	void update();
	STATE getCurrentStateName();
	void setInitialState(State* initial_);
};
#endif;

