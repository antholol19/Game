#pragma once
#include <SDL.h>
#include "Constants.h"


const int WALL_THICKNESS = 15;

class Wall
{
public:
	Wall();
	~Wall();
	void draw(SDL_Renderer* renderer);
private:
	SDL_Rect wall_;
};

