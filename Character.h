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

using namespace std;

class Character  //NPC
{
private:
	class KinematicBody* body;
	class Scene* scene;
	Path* path;
	// Decider variable to hold the Decision Tree
	DecisionTreeNode* decider;
	StateMachine* stateMachine;
	

	void SteerToSeekPlayer(SteeringOutput* steering);     
	void SteerToFleePlayer(SteeringOutput* steering);
	void SteerToArriveToPlayer(SteeringOutput* steering);
	void SteerToFollowPath(SteeringOutput* steering);

	//int steerType; //dont need steer types as we are using decision making now
					// each steer type should now be its own action

	
public:

	// Construct char defining an int that selects a steering algorithm
	Character()
	{
		body = NULL;
		scene = NULL;
		//steerType = steerType_;
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


	Vec3 getPos();
	Vec3 getPlayerPos();
	// Set the position of a character to a node in the tile grid
	void SetSpawnPoint(Node* node_);
	// Set the path of tiles to follow
	void setPath(Path* path_) { path = path_; }
	// Return the body of the character
	KinematicBody* getBody() { return body; }

	// Decision making
	bool readDecisionTreeXML(string filename_);
	bool readStateMachineXML(string filename_);

};

#endif

