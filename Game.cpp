#include "Game.h"
#include <iostream>
#include <string>

Game::Game() {}
Game::~Game() {}

void Game::setup(const char* title, int x_pos, int y_pos, int w, int h, bool fullscreen) 
{
	int screen = 0;
	if (fullscreen)
	{
		screen = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		window = SDL_CreateWindow(title, x_pos, y_pos, w, h, screen);
		rend = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Game::set_players() 
{
	Input players;
	players.input_window("Enter number of players:");
	std::cout << players.show_input() << std::endl;
	num_of_players = players.show_input();
	if (num_of_players == 0)
		isRunning = false;
}

void Game::eventHandler()
{
	SDL_Event ev;
	SDL_PollEvent(&ev);

	switch (ev.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:;
	}
}

void Game::render()
{
	int SDL_RenderClear(SDL_Renderer*);
	void SDL_RenderPresent(SDL_Renderer*);
}

void Game::update() {}

void Game::cleanup()
{
	//	~Game();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
}