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
	blinky = nullptr;
}

Scene2::~Scene2()
{
	// memory clean ups
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}

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
			Vec3 tilePos = Vec3(x, y, 0);
			n = new Node(label, tilePos);
			sceneNodes.push_back(n);
			
			// Testing geting node position ================================================================================
			Vec3 nodePos = n->getPosition();
			cout << "Node Label-> (" << label << ") is at position: " << nodePos.x << "," << nodePos.y << endl;
			// =============================================================================================================

			if (find(blockedTiles.begin(), blockedTiles.end(), label) != blockedTiles.end())
			{
				t = new Tile(n, tilePos, tileWidth, tileHeight, this, true); // Create blocked tile
			}
			else
			{
				t = new Tile(n, tilePos, tileWidth, tileHeight, this, false); //create regular tile
			}
			tiles[i][j] = t;
			j++;
			label++;
		}
		j = 0;
		i++;
	}
}

void Scene2::calculateConnectionWeights()
{
	int rows = tiles.size();
	int cols = tiles[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//[i+1][j-1]     [i+1][j]    [i+1][j+1]
			// [i][j-1]       [i][j]     [i][j+1]
			//[i-1][j-1]     [i-1[j]     [i-1][j+1]

			Tile* fromTile = tiles[i][j];
			int from = fromTile->getNode()->getLabel();

			// left: [i][j-1]
			if (j > 0)
			{
				// Suppose each tile had a status that was either walkable or blocked
				
				// if "to" tile is walkbale then add the weight connection
				if (!tiles[i][j - 1]->isBlocked())
				{
					int to = tiles[i][j - 1]->getNode()->getLabel();
					graph->addWeightConnection(from, to, tileWidth);
				}
				 
			}
			// right: [i][j+1]
			if (j < cols - 1)
			{
				if (!tiles[i][j + 1]->isBlocked())
				{
					int to = tiles[i][j + 1]->getNode()->getLabel();
					graph->addWeightConnection(from, to, tileWidth);
				}
				
			}
			// above: [i+1][j]
			if (i < rows - 1)
			{
				if (!tiles[i + 1][j]->isBlocked())
				{
					int to = tiles[i + 1][j]->getNode()->getLabel();
					graph->addWeightConnection(from, to, tileHeight);
				}
				
			}
			// below: [i-1[j]
			if (i > 0)
			{
				if (!tiles[i - 1][j]->isBlocked())
				{
					int to = tiles[i - 1][j]->getNode()->getLabel();
					graph->addWeightConnection(from, to, tileHeight);
				}
				
			}
		}
	}
}

bool Scene2::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	
	// setup and create tiles
	tileWidth = 4.2f;
	tileHeight = 3.0f;
	int cols = ceil((xAxis - 0.5f * tileWidth) / tileWidth);
	int rows = ceil((yAxis - 0.5f * tileHeight) / tileHeight);
	createTiles(rows, cols);

	// create the graph and add the list of nodes to the graph
	graph = new Graph();
	graph->OnCreate(sceneNodes);
	if (!graph->OnCreate(sceneNodes))
	{
		cerr << "Error creating nodes" << endl;
		return false;
	}
	// create connections
	calculateConnectionWeights();

	// Call dijksra to find shortest path
	path = graph->Dijkstra(0, 15);

	// Print the node labels of the shortest path
	if (path.empty())
	{
		cout << "No path found by Dijkstra." << endl;
	}
	else
	{
		cout << "Shortest path found by Dijkstra:";
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

	// setup npcs
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	blinky = new Character(4, path);
	if (!blinky->OnCreate(this) || !blinky->setTextureWidth("Blinky.png"))
	{
		return false;
	}

	return true;
}

void Scene2::OnDestroy()
{
// Memory cleanups
	// NPCs
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
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



void Scene2::Update(const float time) 
{
	blinky->Update(time);

}

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

	blinky->Render(0.15);
	// end of render call
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event) {}
