#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Ball.h"
#include "Paddle.h"

// Vector2 struct just stores x/y coordinates
// (for now)
/*
struct Vector2
{
	float x;
	float y;
};
*/

class Game
{
public:
	Game();
	~Game();
	// Initialize the game
	bool initialize();
	// Run the game until it stops
	void runLoop();
	// shutdown the game
	void shutDown();



private:
	// process user inputs
	void processInput();
	// Update the components of the game
	void updateGame();
	// Generate the sprites 
	void generateOutput();

	/*
	// Load all the actors
	void loadData();
	void unloadData();
	*/

	bool intersect(Ball& ball, Paddle& paddle);

	bool isRunning_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	Uint32 ticksCount_;

	Wall* wall_;
	Ball* ball_;
	Paddle* paddle_;

	// make an actor class to store all game objects
	// objects will inherit from the actor class
	// it will get the position and speed of objects
	// x and y position will be store in a struct
	// std::vector<Actor*> actors_

};

