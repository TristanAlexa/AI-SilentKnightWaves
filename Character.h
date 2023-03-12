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

using namespace std;

class Character  //NPC
{
private:
	class KinematicBody* body;
	class Scene* scene;
	class Path* path;
	vector<Node*> nodes;

	void SteerToSeekPlayer(SteeringOutput* steering);     
	void SteerToFleePlayer(SteeringOutput* steering);
	void SteerToArriveToPlayer(SteeringOutput* steering);
	void SteerToFollowPath(SteeringOutput* steering);

	int steerType;

	
public:

	// Construct char defining an int that selects a steering algorithm
	Character(int steerType_)
	{
		body = NULL;
		scene = NULL;
		steerType = steerType_;
		path = new Path(nodes);
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

	// Set the position of a character to a node in the tile grid
	void SetSpawnPoint(Node* node_);
	// Set the path of tiles to follow
	void setPath(Path* path_) { path = path_; }
	
};

#endif

