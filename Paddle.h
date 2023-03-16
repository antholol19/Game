#pragma once
#include <SDL.h>
#include "Math.h"
#include "Wall.h"

const float PADDLE_HEIGHT = 100.0f;
const int PADDLE_THICKNESS = 10;

class Paddle
{
public:
	Paddle();
	~Paddle();

	void update(float deltaTime);
	void handleInput();
	void draw(SDL_Renderer* renderer);
	Vector2D getPosition() const { return pos_; }

private:
	
	Vector2D pos_;
	//int xPos_, yPos_;
	int dir_;
	SDL_Rect paddle_;
};

