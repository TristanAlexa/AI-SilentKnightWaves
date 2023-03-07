#include "Tile.h"

Tile::Tile(float width_, float height_, Scene* scene_)
{
	width = width_;
	height = height_;
	r = 255;
	g = 255;
	b = 255;
	a = 0;
	scene = scene_;
}

void Tile::Render()
{
	// Scene has a reference to the gamemanager, which can call getRenderer()
	SDL_Renderer* renderer = scene->game->getRenderer();

	SDL_Rect rect;
	Vec3 topLeft;
	Vec3 bottomRight;

	Vec3 topLeftScreenCoords;
	Vec3 bottomRightScreenCoords;

	// eveneutally want the position of the tiles from the node. but for now hardcoding the tiles center position
	Vec3 pos = Vec3(8.0f, 5.5f, 0.0f);

	// extend from the center of tile to create the topLeft and bottomRight positions
	topLeft = Vec3(pos.x - 0.5f * width, pos.y + 0.5f * height, 0.0f);
	bottomRight = Vec3(pos.x + 0.5f * width, pos.y - 0.5f * height, 0.0f);

	topLeftScreenCoords = scene->getProjectionMatrix() * topLeft;
	bottomRightScreenCoords = scene->getProjectionMatrix() * bottomRight;

	// Set the pos, width and height of the tile using world coords
	rect.x = static_cast<int>(topLeftScreenCoords.x);
	rect.y = static_cast<int>(topLeftScreenCoords.y);
	rect.w = static_cast<int>(bottomRightScreenCoords.x - topLeftScreenCoords.x);
	rect.h = static_cast<int>(bottomRightScreenCoords.y - topLeftScreenCoords.y);

	// draw the tile with colour (you could use images and texutres if want)
	setRGBA(17, 138, 178, 255);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);

	// draw border around tile
	setRGBA(255, 255, 255, 0);
	SDL_RenderDrawRect(renderer, &rect);
}
