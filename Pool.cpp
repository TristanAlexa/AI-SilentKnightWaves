#include "Pool.h"
#include "GameManager.h"

Pool::Pool()
{
	// Initializing all the objects to be in a list
	head = &objects[0];
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		objects[i].SetNext(&objects[i + 1]);
	}
	objects[POOL_SIZE - 1].SetNext(NULL);
}

bool Pool::OnCreate(GameManager* game_)
{
	game = game_;
	for (int i = 0; i < POOL_SIZE; i++)
	{
		// return false if oncreate of a particle returns false;
		if (!objects[i].OnCreate(game->getRenderer()))
		{
			return false;
		}
	}
	return true;
}

void Pool::createParticle(Vec3 pos, Vec3 vel, int lifetime, float oritentation)
{
	//handle empty pool
	if (head == NULL) return;

	// remove first available particle
	Particle* newParticle = head;
	head = newParticle->GetNext();

	newParticle->Init(pos, vel, lifetime, oritentation);
}

void Pool::update(float deltaTime)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (objects[i].Update(deltaTime))
		{
			//add particles to front of the stack
			objects[i].SetNext(head);
			head = &objects[i];
		}
	}
}

void Pool::render(GameManager* game_)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		objects[i].Render(game);
	}
}
