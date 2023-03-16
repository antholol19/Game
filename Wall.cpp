#include "Wall.h"

Wall::Wall()
{
    // Initialize the wall
	wall_.x = 0;
    wall_.y = 0;
    wall_.w = 0;
    wall_.h = 0;

}

Wall::~Wall()
{

}

void Wall::draw(SDL_Renderer* renderer) 
{
	// Draw walls
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// Draw top wall
	wall_.x = 0;
	wall_.y = 0;
	wall_.w = SCREEN_WIDTH;
	wall_.h = WALL_THICKNESS;

	SDL_RenderFillRect(renderer, &wall_);

	// Draw bottom wall
	wall_.y = SCREEN_HEIGHT - WALL_THICKNESS;
	SDL_RenderFillRect(renderer, &wall_);

	// Draw right wall
	wall_.x = SCREEN_WIDTH - WALL_THICKNESS;
	wall_.y = 0;
	wall_.w = WALL_THICKNESS;
	wall_.h = SCREEN_HEIGHT;
	SDL_RenderFillRect(renderer, &wall_);
}
