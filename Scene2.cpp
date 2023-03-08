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
	tileWidth = 0.0f;
	tileHeight = 0.0f;
}

Scene2::~Scene2()
{
	// memory clean ups
	if (graph)
	{
		delete graph;
	}
	// Loop through the rows of the 2D matrix
	for (int i = 0; i < tiles.size(); i++)
	{
		// Loop through the columns of the current row
		for (int j = 0; j < tiles[i].size(); j++)
		{
			// Delete the tile at the current position
			delete tiles[i][j];
		}
		tiles[i].clear();
	}
	tiles.clear();
}

/* Resizes the matrix to have a specified number of rowsand coloums
   Create a new node for each row and coloumn and set its position at half the size of the current tiles width and height values
   Create a new tile object and store it at the current row and column node position using tiles[i][j] */
void Scene2::createTiles(int rows_, int cols_)
{
	tiles.resize(rows_);
	for (int i = 0; i < rows_; i++)
	{
		tiles[i].resize(cols_);
	}

	Node* n;
	Tile* t;
	int i, j, label;

	i = 0; //rows
	j = 0; //coloumns
	label = 0; // grid tile number

	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight)
	{
		for (float x = 0.5f * tileWidth; x < xAxis; x += tileWidth)
		{
			//create tiles and nodes
			n = new Node(label);
			Vec3 tilePos = Vec3(x, y, 0);
			t = new Tile(n, tilePos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			j++;
			label++;
		}
		j = 0;
		i++;
	}
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

	// setup and create tiles
	tileWidth = 1.8f;
	tileHeight = 1.7f;
	int cols = ceil((xAxis - 0.5f * tileWidth) / tileWidth);
	int rows = ceil((yAxis - 0.5f * tileHeight) / tileHeight);
	createTiles(rows, cols);

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
	// Memory cleanups
		// NODES
	for (int i = 0; i < sceneNodes.size(); i++)
	{
		delete sceneNodes[i];
	}

		// GRAPH
	if (graph)
	{
		delete graph;
	}

		// TILES
	// Loop through the rows of the 2D matrix
	for (int i = 0; i < tiles.size(); i++)
	{
		// Loop through the columns of the current row
		for (int j = 0; j < tiles[i].size(); j++)
		{
			// Delete the tile at the current position
			delete tiles[i][j];
		}
		tiles[i].clear();
	}
	tiles.clear();
}



void Scene2::Update(const float time) {}

void Scene2::Render()
{
	// clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render all tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			tiles[i][j]->Render();
		}
	}

	// end of render call
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event) {}
