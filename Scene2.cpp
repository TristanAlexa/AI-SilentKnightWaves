#include "Scene2.h"
using namespace std;
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
	int count = 5;
	sceneNodes.resize(count);

	// create some nodes
	// TODO delete them later!!
	for (int i = 0; i < count; i++)
	{
		sceneNodes[i] = new Node(i);

	}

	// create the graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		// include error message
		return false;
	}

	// set up graph and test it
	//     0
	//     |
	// 1 - 2 - 3
	//     |
	//     4

	// connections from 0
	graph->addWeightConnection(
		sceneNodes[0]->getLabel(),
		sceneNodes[2]->getLabel(),
		1.0f
	);

	//connections from 1
	graph->addWeightConnection(1, 2, 1.0f);

	//connections from 2
	graph->addWeightConnection(2, 0, 1.0f);
	graph->addWeightConnection(2, 1, 1.0f);
	graph->addWeightConnection(2, 3, 1.0f);
	graph->addWeightConnection(2, 04, 1.0f);

	// connections from 3
	graph->addWeightConnection(3, 2, 1.0f);

	//connections from 4
	graph->addWeightConnection(3, 2, 1.0f);

	cout << "Scene 2" << endl;

	int currNode = 1;
	cout << "neighbours of " << currNode << endl;
	for (auto nodeLabel : graph->neighbours(currNode))
	{
		cout << "node " << nodeLabel << endl;
	}

	//call dijksra
	vector<int> path = graph->Dijkstra(0, 4);
	return true;
}

void Scene2::OnDestroy()
{
	//memory clean up
}

void Scene2::Update(const float time){}

void Scene2::Render(){}

void Scene2::HandleEvents(const SDL_Event& event){}
