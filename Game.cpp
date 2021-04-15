#include "Game.h"
#include <iostream>

Game::Game() 
{
	isRunning = true;
	num_of_cards = 0;
	window = nullptr;
	rend = nullptr;
}
Game::~Game() {}

void Game::setup(const char* title, int x_pos, int y_pos, int w, int h, bool fullscreen) 
{
	int screen = 0;
	if (fullscreen)
		screen = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		isRunning = false;

	window = SDL_CreateWindow(title, x_pos, y_pos, w, h, screen);
	rend = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

}

void Game::setPlayers() 
{
	int players = getInput("Enter the number of players:");
	if (players != 0)
		for (int i = 1; i <= players; i++)
			num_of_players.push_back(Player(i));
	else
		isRunning = false;
}

void Game::setCards()
{
	int cards = getInput("Enter the (even) number of cards");
	if (cards != 0 || cards % 2 == 0)
		num_of_cards = cards;
	else
		isRunning = false;
}

int Game::getInput(const char* display_text)
{
	Input value;
	value.inputWindow(display_text);
	return value.inputShow();
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
		case SDL_MOUSEBUTTONDOWN:
			std::cout << ev.button.x << std::endl;
			std::cout << ev.button.y << std::endl;
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