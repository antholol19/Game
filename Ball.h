#pragma once
#include <SDL.h>
#include "Constants.h"
#include "Math.h"

const int BALL_THICKNESS = 10;

class Ball
{
public:
	Ball();
	~Ball();

	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	Vector2D getPosition() const { return pos_; }
	Vector2D getVelocity() const { return vel_; }
	void setVelocity(const Vector2D& vel) {
		vel_ = vel;
	}

private:
	Vector2D pos_;
	Vector2D vel_;

	//int xVel_, yVel_;
	SDL_Rect ball_;
};

