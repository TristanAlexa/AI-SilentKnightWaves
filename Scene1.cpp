#include "Scene1.h"
#include "VMath.h"
/*
	In class demo code
*/

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a staticbody NPC
	myNPC = nullptr;

	// creates a character using a dynamic body
	blinky = nullptr;
}

Scene1::~Scene1(){
	if (blinky) 
	{
		blinky->OnDestroy();
		delete blinky;
	}

	if (myNPC)
	{
		delete myNPC;
	}
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this

	Vec3 position = Vec3(5.0f,3.5f,0.0f);
	/*Vec3 velocity = Vec3(1.0f,1.0f,1.0f);
	Vec3 acceleration = Vec3();*/
	//float mass = 1.0f;
	float orientation = 0.0f;
	float maxSpeed = 5.0f;   //want to make max speed of ncp smaller than player
	float maxRotation = 3.0f;
	myNPC = new StaticBody(
		position,
		orientation,
		maxSpeed,
		maxRotation
		);
	image = IMG_Load("Clyde.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	myNPC->setTexture(texture);
	SDL_FreeSurface(image);

	
	blinky = new Character(3);
	if (!blinky->OnCreate(this) || !blinky->setTextureWidth("Blinky.png") )
	{
		return false;
	}

	// end of character set ups
	return true;
}

void Scene1::OnDestroy() {
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}

	if (myNPC)
	{
		delete myNPC;
	}
}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's

	Body* player;                              //player pointer is a pointer to body
	player = game->getPlayer();                //returns a pointer to a player body

	/// STEERING calculation
	KinematicSteeringOutput* steering;
	steering = NULL;

	/// Creating Kinematic Wander 
	KinematicWander* steeringAlgorithm;
	steeringAlgorithm = new KinematicWander(myNPC);
	steering = steeringAlgorithm->getSteering();


	/// Update player and characters
	myNPC->Update(deltaTime, steering);   // orange ghost using kinematic seek-> moves towards player and spins in place under player
										  // orange ghost using kinematic arrive-> stops at the corner of the player img
	blinky->Update(deltaTime);            // red ghost using dynamic seek to slow down and ocilates around player
	game->getPlayer()->Update(deltaTime);

	/// Memory clean up
	if (steeringAlgorithm)
	{
		delete steeringAlgorithm;
	}
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	// Create SDL rectangle, and populate data
	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// convert the position from game coords to screen coords
	screenCoords = projectionMatrix * myNPC->getPos();
	float scale = 0.15f;
	SDL_QueryTexture(myNPC->getTexture(), nullptr, nullptr, &w, &h);

	// The square's x and y values represent the top left corner of
	// where SDL will draw the .png image
	// The 0.5f * w/h offset is to place the .png so that pos represents the center
	// (Note the y axis for screen coords points downward, hence subtractions!!!!)
	square.w = static_cast<int>(w*scale);
	square.h = static_cast<int>(h*scale);
	square.x = static_cast<int>(screenCoords.x - 0.5f * square.w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * square.h);

	float orientation = myNPC->getOrientation();
	// Convert character orientation from radians to degrees.
	float orientationDegrees = orientation * 180.0f / M_PI;

	// Render the NPC
	SDL_RenderCopyEx(renderer, myNPC->getTexture(), nullptr, &square,
         orientationDegrees, nullptr, SDL_FLIP_NONE);

	
	blinky->render(0.15f);

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
