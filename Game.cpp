#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

Game::Game() 
{
	this->isRunning = true;
	this->num_of_cards = 0;
	this->window = nullptr;
	this->rend = nullptr;
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

void Game::set_players() 
{
	int players = get_input("Enter the number of players:");
	if (players != 0)
		for (int i = players; i > 0; i--)
			num_of_players.push_back(Player(i));
	else
		isRunning = false;
}

void Game::set_cards()
{
	int cards = get_input("Enter the (even) number of cards");
	if (cards != 0 || cards % 2 == 0)
		num_of_cards = cards;
	else
		isRunning = false;
}

int Game::get_input(const char* display_text)
{
	Input value;
	value.input_window(display_text);
	return value.show_input();
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