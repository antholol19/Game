#include "Paddle.h"



Paddle::Paddle() 
	: dir_(0)
{
	pos_.x = 10.0f;
	pos_.y = static_cast<float>(SCREEN_HEIGHT) / 2.0f;
	paddle_.x = static_cast<int>(pos_.x);
	paddle_.y = static_cast<int>(pos_.y);
	paddle_.w = PADDLE_THICKNESS;
	paddle_.h = static_cast<int>(PADDLE_HEIGHT);
}
Paddle::~Paddle() 
{

}

void Paddle::update(float deltaTime) 
{
	// Update paddle position based on direction
	if (dir_ != 0)
	{
		pos_.y += dir_ * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (pos_.y < (PADDLE_HEIGHT / 2.0f + WALL_THICKNESS))
		{
			pos_.y = PADDLE_HEIGHT / 2.0f + WALL_THICKNESS;
		}
		else if (pos_.y > (static_cast<float>(SCREEN_HEIGHT) - PADDLE_HEIGHT / 2.0f - WALL_THICKNESS))
		{
			pos_.y = static_cast<float>(SCREEN_HEIGHT) - PADDLE_HEIGHT / 2.0f - WALL_THICKNESS;
		}
	}

}

void Paddle::handleInput()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	// Update paddle direction based on W/S keys
	dir_ = 0;
	if (currentKeyStates[SDL_SCANCODE_W])
	{
		dir_ -= 1;
	}
	if (currentKeyStates[SDL_SCANCODE_S])
	{
		dir_ += 1;
	}
}

void Paddle::draw(SDL_Renderer* renderer) 
{
	// Draw paddle
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	paddle_.x = static_cast<int>(pos_.x);
	paddle_.y = static_cast<int>(pos_.y - PADDLE_HEIGHT / 2);

	SDL_RenderFillRect(renderer, &paddle_);
}
