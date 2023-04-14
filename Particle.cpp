#include "Particle.h"
#include "GameManager.h"

bool Particle::OnCreate(SDL_Renderer* renderer)
{
    image = IMG_Load("Pinky.png");
    if (image == NULL)
    {
        std::cerr << "Cant open Pinky image" << std::endl;
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == NULL)
    {
        std::cerr << "Cant create texture from surface in particle.h" << std::endl;
        return false;
    }
    return true;
}

bool Particle::Update(float deltaTime)
{
    if (!InUse()) return false;

    framesLeft--;
    live.pos += live.vel * deltaTime;

    return framesLeft == 0;
}

void Particle::Render(GameManager* game)
{
    if (!InUse()) return;

    SDL_Renderer* renderer = game->getRenderer();
    Matrix4 projectionMatrix = game->getProjectionMatrix();

    SDL_Rect rect;
    Vec3 screenCoords;

    float w, h;
    float scale = 0.1;

    screenCoords = projectionMatrix * live.pos;
    w = image->w * scale;
    h = image->h * scale;

    rect.x = static_cast<int>(screenCoords.x - 0.5 * w);
    rect.y = static_cast<int>(screenCoords.y - 0.5 * h);
    rect.w = static_cast<int>(w);
    rect.h = static_cast<int>(h);

    // if using orientation, might need to convert between radians and degrees
    // currently dont have to since orientation is defaulted to 0

    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, live.orientation, nullptr, SDL_FLIP_NONE);
}
