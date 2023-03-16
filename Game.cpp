#include "Game.h"

Game::Game()
	: window_(nullptr)
	, renderer_(nullptr)
	, isRunning_(false)
	, ticksCount_(0)
	, wall_(nullptr)
	, ball_(nullptr)
	, paddle_(nullptr)
{
	
}

Game::~Game()
{
	delete wall_;
	delete ball_;
	delete paddle_;

}

bool Game::initialize() 
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("SDL could not initialize! %s", SDL_GetError());
		return false;
	}
	// Create window
	window_ = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window_ == nullptr) {
		SDL_Log("SDL failed to create a window! %s", SDL_GetError());
		return false;
	}
	// Create renderer
	renderer_ = SDL_CreateRenderer(window_, -1, 0);
	if (renderer_ == nullptr) {
		SDL_Log("SDL failed to create renderer! %s", SDL_GetError());
		return false;
	}
	wall_ = new Wall();
	ball_ = new Ball();
	paddle_ = new Paddle();

	isRunning_ = true;
	return true;
}

void Game::runLoop() 
{
	// Run the game until it is over
	while (isRunning_) {
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::shutDown() 
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}


void Game::processInput() 
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		// User request quit
		switch (e.type) 
		{
			case SDL_QUIT:
				isRunning_ = false;
				break;

		}
	}
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_ESCAPE])
	{
		isRunning_ = false;
	}
	paddle_->handleInput();
}

void Game::updateGame() 
{
	// Update the time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount_ + 16));

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - ticksCount_) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	ticksCount_ = SDL_GetTicks();
	paddle_->update(deltaTime);
	ball_->update(deltaTime);
	
	bool collide = intersect(*ball_, *paddle_);
}

void Game::generateOutput()
{
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

	// Clear back buffer
	SDL_RenderClear(renderer_);

	wall_->draw(renderer_);
	paddle_->draw(renderer_);
	ball_->draw(renderer_);

	// Swap front buffer and back buffer
	SDL_RenderPresent(renderer_);
}


bool Game::intersect(Ball& ball, Paddle& paddle) {
	// Bounce if needed


	// Did the ball intersect with the paddle?

	float diff = paddle.getPosition().y - ball.getPosition().y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= PADDLE_HEIGHT / 2.0f &&
		// We are in the correct x-position
		ball.getPosition().x <= 25.0f && ball.getPosition().x >= 20.0f &&
		// The ball is moving to the left
		ball.getVelocity().x < 0.0f)
	{
		ball.setVelocity(Vector2D(ball.getVelocity().x * -1.0f, ball.getVelocity().y));
		return true;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (ball.getPosition().x <= 0.0f)
	{
		isRunning_ = false;
		return false;
	}
	// Did the ball collide with the right wall?
	else if (ball.getPosition().x >= (SCREEN_WIDTH - WALL_THICKNESS) && ball.getVelocity().x > 0.0f)
	{
		ball.setVelocity(Vector2D(ball.getVelocity().x * -1.0f, ball.getVelocity().y));
		return true;
	}

	// Did the ball collide with the top wall?
	if (ball.getPosition().y <= WALL_THICKNESS && ball.getVelocity().y < 0.0f)
	{
		ball.setVelocity(Vector2D(ball.getVelocity().x, ball.getVelocity().y * -1.0f));
		return true;
	}
	// Did the ball collide with the bottom wall?
	else if (ball.getPosition().y >= (SCREEN_HEIGHT - WALL_THICKNESS) &&
		ball.getVelocity().y > 0.0f)
	{
		ball.setVelocity(Vector2D(ball.getVelocity().x, ball.getVelocity().y * -1.0f));
		return true;
	}
	return false;
}
