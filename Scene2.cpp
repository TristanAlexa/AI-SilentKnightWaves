#include "Scene2.h"
using namespace std;
Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_)
{
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
	graph = NULL;
	singleTile = NULL;
}

void Scene2::createTiles()
{
	Vec3 tilePos = Vec3(15.0f, 5.0f, 5.0f);
	singleTile = new Tile(tilePos, 2.0f, 1.5f, this);
}

Scene2::~Scene2()
{
	// memory clean ups
}

bool Scene2::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	int count = 5;
	sceneNodes.resize(count);

	// create some nodes
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
	graph->addWeightConnection(2, 4, 1.0f);

	// connections from 3
	graph->addWeightConnection(3, 2, 1.0f);

	//connections from 4
	graph->addWeightConnection(3, 2, 1.0f);

	cout << "Scene 2" << endl;

	int currNode = 1;
	cout << "neighbours of node(" << currNode << ") are: ";
	for (auto nodeLabel : graph->neighbours(currNode))
	{
		cout << "node (" << nodeLabel << ")" << endl;
	}

	// create tiles
	createTiles();

	// Call dijksra to find shortest path
	vector<int> path = graph->Dijkstra(0, 4);

	// Print the node labels of the shortest path
	if (path.empty())
	{
		cout << "No path found." << endl;
	}
	else
	{
		cout << "Shortest path:";
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i];
			if (i < path.size() - 1)
			{
				cout << " -> ";
			}
		}
		cout << endl;
	}
	return true;
}

void Scene2::OnDestroy()
{
	// Clean up all the sceneNodes created
	for (int i = 0; i < sceneNodes.size(); i++)
	{
		delete sceneNodes[i];
	}
}

void Scene2::Update(const float time){}

void Scene2::Render()
{
	// clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render the tiles
	singleTile->Render();

	// end of render call
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event){}
