#include "Character.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;

	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 4.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		body = new KinematicBody(
			Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
			radius,
			orientation,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular
		);
	}

	if (!body)
	{
		return false;
	}

	return true;
}

bool Character::setTextureWidth(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture) 
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	body->setTexture(texture);
	return true;
}

void Character::Update(float deltaTime)
{
	// create a new overall steering output
	SteeringOutput* steering;
	steering = new SteeringOutput();

	if (stateMachine != NULL)
	{
		stateMachine->update();
		switch (stateMachine->getCurrentStateName())
		{
		case STATE::SEEK:
			SteerToSeekPlayer(steering);
			break;
		case STATE::FLEE:
			SteerToFleePlayer(steering);
			break;
		case STATE::ARRIVE:
			SteerToArriveToPlayer(steering);
			break;
		case STATE::FOLLOWAPATH:
			SteerToFollowPath(steering);
			break;
		case STATE::DO_NOTHING:
			getBody()->setVel(Vec3(0.0f, 0.0f, 0.0f));
			break;
		}
	}
	
	// apply the steering to the equations of motion
	body->Update(deltaTime, steering);

	// clean up memory
	// (delete only those objects created in this function)
	if (steering)
	{
		delete steering;
	}
}

void Character::SteerToSeekPlayer(SteeringOutput* steering)
{
	vector<SteeringOutput*> steering_outputs;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)
	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algorithm = new Seek(body, target); //dynamic steering algo's should derive from the base steeringBehaviour class
	
	//SteeringBehaviour* steering_algorithm = new Arrive(body, target); // shoudl be in its own helper function

	steering_outputs.push_back(steering_algorithm->getSteering());

	// add in some other algorithms

	// Add together steering outputs
	for (int i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	// clean up memory
	// (delete only those objects created in this function)
	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}

void Character::SteerToFleePlayer(SteeringOutput* steering)
{
	vector<SteeringOutput*> steering_outputs;

	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algorithm = new Flee(body, target); 

	steering_outputs.push_back(steering_algorithm->getSteering());

	// add in some other algorithms

	// Add together steering outputs
	for (int i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}

void Character::SteerToArriveToPlayer(SteeringOutput* steering)
{
	vector<SteeringOutput*> steering_outputs;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)
	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algorithm = new Arrive(body, target); 

	steering_outputs.push_back(steering_algorithm->getSteering());

	// add in some other algorithms

	// Add together steering outputs
	for (int i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	// clean up memory
	// (delete only those objects created in this function)
	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}

void Character::SteerToFollowPath(SteeringOutput* steering)
{
	vector<SteeringOutput*> steering_outputs;
	Body* target = new Body();
	
	SteeringBehaviour* steering_algorithm = new FollowAPath(body, target, path);
	steering_outputs.push_back(steering_algorithm->getSteering());

	// Add together steering outputs
	for (int i = 0; i < steering_outputs.size(); i++)
	{
		if (steering_outputs[i])
		{
			*steering += *steering_outputs[i];
		}
	}

	// clean up memory
	// (delete only those objects created in this function)
	if (steering_algorithm)
	{
		delete steering_algorithm;
	}
}

void Character::HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.scancode)
		{
		// To simulate combat: when E is pressed, the char will take damage, lowering its health
		case SDL_SCANCODE_E:
			setHealth(health - 1);
			cout << "Blinky took damage!" << endl;
			cout << "Blinky's current Health Points: " << health << endl;
			break;

		// To simulate AI healing itself
		case SDL_SCANCODE_R:
			setHealth(3);
			cout << "Blinky healed itself!" << endl;
			cout << "Blinky's current Health Points: " << health << endl;
			break;
		}
	}
}

void Character::Render(float scale)
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);
}

Vec3 Character::getPos()
{
	return body->getPos();
}

Vec3 Character::getPlayerPos()
{
	return scene->game->getPlayer()->getPos();
}

void Character::SetSpawnPoint(Node* node_)
{
	body->setPos(node_->getPosition());
}

int Character::getHealth()
{
	return health;
}

bool Character::readStateMachineXML(string filename_)
{
	stateMachine = new StateMachine();

	// Define character states
	State* followAPath = new State(STATE::FOLLOWAPATH);
	State* arriveToPlayer = new State(STATE::ARRIVE);
	State* fleePlayer = new State(STATE::FLEE);
	State* doNothing = new State(STATE::DO_NOTHING); 

	// Character's default state is to follow the set path
	stateMachine->setInitialState(followAPath);

	/* While AI is following the path, if the player comes in range,
	   the AI will transition to arrive to the player*/
	Condition* ifInRange = new ConditionInRange(this);
	followAPath->addTransition(new Transition(ifInRange, arriveToPlayer));

	/* While AI is following the player, if the player moves out of range,
	   the AI will transition back to the default state*/
	Condition* ifOutOfRange = new ConditionOutOfRange(this);
	arriveToPlayer->addTransition(new Transition(ifOutOfRange, followAPath));

	/* When the AI is following the player and gets in range of a jail cell,
	   the AI will transition to do nothing. Its trapped*/
	Condition* ifInJail = new ConditionInJail(this); 
	arriveToPlayer->addTransition(new Transition(ifInJail, doNothing));

	/* If the AI is following the player, and if the AI's health drops below a threshold
	   the AI will transition to flee the player*/
	Condition* ifLowHealth = new ConditionLowHealth(this);
	arriveToPlayer->addTransition(new Transition(ifLowHealth, fleePlayer));

	/* If the AI is fleeing the player, and manages to return back to full health,
	   the AI will transition back to the default state of following its path*/
	Condition* ifHealthy = new ConditionHealthy(this);
	fleePlayer->addTransition(new Transition(ifHealthy, followAPath));

	return true;
}