#include "Ball.h"
Ball::Ball()
{
	pos_.x = static_cast<float>(SCREEN_WIDTH) / 2.0f;
	pos_.y = static_cast<float>(SCREEN_WIDTH) / 2.0f;
	vel_.x = -200.0f;
	vel_.y = 235.0f;

	ball_.x = pos_.x;
	ball_.y = pos_.y;
	ball_.w = BALL_THICKNESS;
	ball_.h = BALL_THICKNESS;
}

Ball::~Ball()
{

}

void Ball::update(float deltaTime)
{
	// Update ball position based on ball velocity
	pos_.x += vel_.x * deltaTime;
	pos_.y += vel_.y * deltaTime;
}

void Ball::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	ball_.x = static_cast<int>(pos_.x - BALL_THICKNESS / 2);
	ball_.y = static_cast<int>(pos_.y - BALL_THICKNESS / 2);

	SDL_RenderFillRect(renderer, &ball_);

}