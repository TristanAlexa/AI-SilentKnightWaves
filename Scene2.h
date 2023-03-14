#ifndef SCENE2_H
#define SCENE2_H

#include "Scene.h"
#include "MMath.h"
#include "Graph.h"
#include "Tile.h"
#include "Character.h"
#include "KinematicArrive.h"
using namespace MATH;
class Scene2 : public Scene
{
private:
	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4     inverseProjection;

	// NPC vars
	Character* blinky;
	// Path finding vars
	Graph* graph;
	vector<Node*> sceneNodes;
	float tileWidth, tileHeight;
	// 2D matrix of tiles
	vector< vector <Tile*> > tiles; 
	// tiles at these node positions will be blocked
	vector<int> blockedTiles = { 13,15,16,17,18,19,20,22, //bottom
								37,39,49,51,			  //left
								44,46,56,58,			  //right
								73,75,76,77,78,79,80,82 };//top                        

	void createTiles(int rows_, int cols_);
	void calculateConnectionWeights();
public:
	
	Scene2(SDL_Window* sdlWindow, GameManager* game_);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
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

