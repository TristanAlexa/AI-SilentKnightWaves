#ifndef MAINGAMESCENE_H
#define MAINGAMESCENE_H

#include "Scene.h"
#include "MMath.h"
#include "StaticBody.h"
#include "KinematicWander.h"
#include "Character.h"

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

};
#endif;
