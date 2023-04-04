#include "MainGameScene.h"

MainGameScene::MainGameScene(SDL_Window* sdlWindow_, GameManager* game_)
{
	// Init window variables
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// Init NPCs
	for (int i = 0; i < 2; i++)
	{
		blinky[i] = nullptr;
	}
	
	tower = nullptr;

	graph = NULL;
	tileWidth = 0.0f;
	tileHeight = 0.0f;
}

MainGameScene::~MainGameScene()
{
	// Memory clean ups
	for (int i = 0; i < 2; i++)
	{
		if (blinky[i])
		{
			blinky[i]->OnDestroy();
			delete blinky[i];
		}
	}
	
	if (tower)
		delete tower;
	if (graph)
	{
		delete graph;
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			delete tiles[i][j];
		}
		tiles[i].clear();
	}
	tiles.clear();

}

bool MainGameScene::OnCreate()
{
	cout << "Main Game Screen Created" << endl;
	// Create window and set projection matrix
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// setup and create tiles
	tileWidth = 2.1f;
	tileHeight = 1.9f;
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

	// Call dijksra to find shortest path and store the path in a Path obj
	int startNode = 85;
	int endNode = 42;
	path[0] = graph->Dijkstra(startNode, endNode);
	Path* p = new Path(path[0]);

	int startNode1 = 95;
	int endNode1 = 42;
	path[1] = graph->Dijkstra(startNode1, endNode1);
	Path* p2 = new Path(path[1]);

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	createTowerObj();

	// Set player image (player created and values initialized in game manager)
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Currently the character constructor defines what steering algorithm to use
	for (int i = 0; i < 2; i++)
	{
		blinky[i] = new Character();
		if (!blinky[i]->OnCreate(this) || !blinky[i]->setTextureWidth("Blinky.png"))
		{
			return false;
		}

		if (!blinky[i]->readStateMachineXML("blinkySM.xml"))
		{
			return false;
		}
	}
	
	blinky[0]->setPath(p);
	blinky[0]->SetSpawnPoint(path[0][0]);
	blinky[1]->setPath(p2);
	blinky[1]->SetSpawnPoint(path[1][0]);
	
	return true;
}

void MainGameScene::OnDestroy()
{
	// Memory clean ups
	for (int i = 0; i < 2; i++)
	{
		if (blinky[i])
		{
			blinky[i]->OnDestroy();
			delete blinky[i];
		}
	}
	if (tower)
		delete tower;
	if (graph)
	{
		delete graph;
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			delete tiles[i][j];
		}
		tiles[i].clear();
	}
	tiles.clear();
}

void MainGameScene::Update(const float deltaTime)
{
	// Calculate and apply any steering for npc's
	KinematicSteeringOutput* steering;
	steering = NULL;

	// Update characters and player
	blinky[0]->Update(deltaTime);
	blinky[1]->Update(deltaTime);

	Body* player;
	player = game->getPlayer();
	game->getPlayer()->Update(deltaTime);
}

void MainGameScene::Render()
{
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

	blinky[0]->Render(0.15f);
	blinky[1]->Render(0.15);
	game->RenderPlayer(0.10f);
	RenderTowerObj(0.3);
	SDL_RenderPresent(renderer);
}

void MainGameScene::HandleEvents(const SDL_Event& event)
{
	// Send events to NPCs as needed
	blinky[0]->HandleEvents(event);
	blinky[1]->HandleEvents(event);
	// Send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

//Creates the grid of tiles 
void MainGameScene::createTiles(int rows_, int cols_)
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

			if (find(blockedTiles.begin(), blockedTiles.end(), label) != blockedTiles.end())
			{
				t = new Tile(n, tilePos, tileWidth, tileHeight, this, true, false); // Create blocked tile
			}
			else if (find(jailTiles.begin(), jailTiles.end(), label) != jailTiles.end())
			{
				t = new Tile(n, tilePos, tileWidth, tileHeight, this, false, true); // create jail tile
			}
			else
			{
				t = new Tile(n, tilePos, tileWidth, tileHeight, this, false, false); //create regular tile
			}
			tiles[i][j] = t;
			j++;
			label++;
		}
		j = 0;
		i++;
	}
}

// Adds a connection weight between each tile and their neighbours if the neighbouring tile is not a blocked tile
void MainGameScene::calculateConnectionWeights()
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

// Creates a new instance Body instance + sets the image and texture for the tower
void MainGameScene::createTowerObj()
{
	SDL_Surface* image;
	SDL_Texture* texture;

	// Set up tower object to be a standstill gameobject
	tower = new Body(Vec3(16.0f, 2.0f, 0.0f), Vec3(), Vec3(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	image = IMG_Load("tower.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	tower->setTexture(texture);
	SDL_FreeSurface(image);
}

// Render the tower objects texture
void MainGameScene::RenderTowerObj(float scale)
{
	// Create SDL rectangle, and populate data
	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// convert the position from game coords to screen coords
	screenCoords = projectionMatrix * tower->getPos();
	SDL_QueryTexture(tower->getTexture(), nullptr, nullptr, &w, &h);

	// The square's x and y values represent the top left corner of
	// where SDL will draw the .png image
	// The 0.5f * w/h offset is to place the .png so that pos represents the center
	// (Note the y axis for screen coords points downward, hence subtractions!!!!)
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = static_cast<int>(w * scale);
	square.h = static_cast<int>(h * scale);

	float orientation = tower->getOrientation();
	// Convert character orientation from radians to degrees.
	float orientationDegrees = orientation * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, tower->getTexture(), nullptr, &square,
		orientationDegrees, nullptr, SDL_FLIP_NONE);
}