#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene2::~Scene2()
{
	// memory clean ups
}

bool Scene2::OnCreate()
{
	// set up graph and test it
	//     0
	//     |
	// 1 - 2 - 3
	//     |
	//     4
	return true;
}

void Scene2::OnDestroy()
{
}

void Scene2::Update(const float time){}

void Scene2::Render(){}

void Scene2::HandleEvents(const SDL_Event& event){}
