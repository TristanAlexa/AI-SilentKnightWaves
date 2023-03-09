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
	vector< vector <Tile*> > tiles;         // 2D matrix
	vector<int> blockedTiles = { 8,13,20 }; // tiles at these node positions will be blocked                       

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
	vector<int> path;
	// retrieve the shortest path from dijkstra
	vector<int> getPath() const { return path; }
};

#endif;

