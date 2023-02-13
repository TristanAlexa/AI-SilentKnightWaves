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
	clyde = nullptr;
	blinky = nullptr;
}

MainGameScene::~MainGameScene()
{
	// Memory clean ups
	if (clyde)
	{
		delete clyde;
	}

	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}

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

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image (player created and values initialized in game manager)
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set up staticbody NPC constructors and images
	// CLYDE: orange
	Vec3 position = Vec3(2.0f, 8.0f, 0.0f);
	float orientation = 0.0f;
	float maxSpeed = 2.5f;
	float maxRotation = 3.5f;
	clyde = new StaticBody(position, orientation, maxSpeed, maxRotation);

	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	clyde->setTexture(texture);
	SDL_FreeSurface(image);


	// Currently the character constructor defines what steering algorithm to use
	blinky = new Character(3); 
	if (!blinky->OnCreate(this) || !blinky->setTextureWidth("Blinky.png"))
	{
		return false;
	}
	return true;
}

void MainGameScene::OnDestroy()
{
	// Memory clean ups
	if (clyde)
	{
		delete clyde;
	}

	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

void MainGameScene::Update(const float deltaTime)
{
	// Calculate and apply any steering for npc's
	KinematicSteeringOutput* steering;
	steering = NULL;

		// Create Kinematic Wander 
	KinematicWander* steeringAlgorithm;
	steeringAlgorithm = new KinematicWander(clyde);
	steering = steeringAlgorithm->getSteering();

	// Update characters and player
	clyde->Update(deltaTime, steering);
	blinky->Update(deltaTime);

	Body* player;
	player = game->getPlayer();
	game->getPlayer()->Update(deltaTime);

	if (steeringAlgorithm)
	{
		delete steeringAlgorithm;
	}
}

void MainGameScene::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// Render the static body Clyde
	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// convert the position from game coords to screen coords
	screenCoords = projectionMatrix * clyde->getPos();
	float scale = 0.15f;
	SDL_QueryTexture(clyde->getTexture(), nullptr, nullptr, &w, &h);

	// The square's x and y values represent the top left corner of
	// where SDL will draw the .png image
	// The 0.5f * w/h offset is to place the .png so that pos represents the center
	// (Note the y axis for screen coords points downward, hence subtractions!!!!)
	square.w = static_cast<int>(w * scale);
	square.h = static_cast<int>(h * scale);
	square.x = static_cast<int>(screenCoords.x - 0.5f * square.w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * square.h);

	float orientation = clyde->getOrientation();
	// Convert character orientation from radians to degrees.
	float orientationDegrees = orientation * 180.0f / M_PI;

	// Render the NPC
	SDL_RenderCopyEx(renderer, clyde->getTexture(), nullptr, &square,
		orientationDegrees, nullptr, SDL_FLIP_NONE);

	//blinkyFlee->Render(0.15f);
	blinky->Render(0.15f);
	game->RenderPlayer(0.10f);
	SDL_RenderPresent(renderer);
}

void MainGameScene::HandleEvents(const SDL_Event& event)
{
	// Send events to NPCs as needed

	// Send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
