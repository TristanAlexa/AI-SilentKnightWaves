#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"
#include "Seek.h"
#include "Flee.h"
#include "Arrive.h"
#include "FollowAPath.h"
#include "Node.h"
#include "Path.h"
#include "Action.h"
#include "Decision.h"
#include "PlayerInRangeDecision.h"
#include "InJailDecision.h"
#include "StateMachine.h"
#include "ConditionInRange.h"
#include "ConditionInJail.h"
#include "ConditionLowHealth.h"
#include "CharacterAdapter.h"

using namespace std;

class Character  //NPC
{
private:
	int health = 3;

	class KinematicBody* body;
	class Scene* scene;
	Path* path;
	
	DecisionTreeNode* decider; //DecisionTree instance
	StateMachine* stateMachine; //StateMachine instance

	CharacterAdapter* myAdapter;

	void SteerToSeekPlayer(SteeringOutput* steering);     
	void SteerToFleePlayer(SteeringOutput* steering);
	void SteerToArriveToPlayer(SteeringOutput* steering);
	void SteerToFollowPath(SteeringOutput* steering);

public:

	// Construct char defining an int that selects a steering algorithm
	Character()
	{
		body = NULL;
		scene = NULL;
		path = NULL;
		decider = NULL;
		stateMachine = NULL;
	};

	~Character()
	{
		if (body) delete body;
	};

	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	bool setTextureWidth(string file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void Render(float scale = 1.0f);

	Vec3 getPos() const;
	Vec3 getPlayerPos() const;
	// Set the position of a character to a node in the tile grid
	void SetSpawnPoint(Node* node_);
	// Set the path of tiles to follow
	void setPath(Path* path_) { path = path_; }
	// Return the body of the character
	KinematicBody* getBody() { return body; }

	// Functions to read and manipulate health variable
	int getHealth();
	void setHealth(int health_) { health = health_; }

	// Decision making
	bool readStateMachineXML(string filename_);
};

#endif

