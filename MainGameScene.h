#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include "Scene.h"
#include "MMath.h"
#include "StaticBody.h"
#include "KinematicWander.h"
#include "Character.h"

#include "Graph.h"
#include "Tile.h"

using namespace MATH;
class MainGameScene : public Scene {

private:
	SDL_Window* window;
	float xAxis;
	float yAxis;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;

	StaticBody* clyde; 	// Orange Ghost - using Kinematic Wander algorithm
	Character* blinky;  // Red Ghost - using dynamic arrive or flee algorithm
	Body* tower;

	Graph* graph; 
	vector<Node*> sceneNodes;
	float tileWidth, tileHeight;
	vector< vector <Tile*> > tiles;
	
	std::vector<int> jailTiles = { 0,11,84,95 }; //four corners
	vector<int> blockedTiles = { 13,15,16,17,18,19,20,22, //bottom
								37,39,49,51,			  //left
								44,46,56,58,			  //right
								73,75,76,77,78,79,80,82 };//top                        

	void createTiles(int rows_, int cols_);
	void calculateConnectionWeights();

	void createTowerObj();
	void RenderTowerObj(float scale);

public:
	MainGameScene(SDL_Window* sdlWindow, GameManager* game_);
	~MainGameScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }

	// vector to store the path found by Dijkstra
	vector<Node*> path;

};
#endif;
