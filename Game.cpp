#include "Game.h"

Game::Game() 
{
	isRunning = true;
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

void Game::getInput()
{
	Fl_Window* win = new Fl_Window(300, 250, "How many?");

	win->begin();
	Fl_Button* play_but = new Fl_Button(100, 200, 70, 30, "Play");
	Fl_Int_Input* num_of_players = new Fl_Int_Input(130, 50, 100, 30, "Players");
	Fl_Int_Input* num_of_rows = new Fl_Int_Input(130, 100, 100, 30, "Number of rows");
	Fl_Int_Input* num_of_coll = new Fl_Int_Input(130, 150, 100, 30, "Number of collumns");
	win->end();

	play_but->callback((Fl_Callback*)playCb, num_of_players);
	win->show();
	Fl::run();

	setPlayers(atoi(num_of_players->value()));
	setCards(atoi(num_of_rows->value()), atoi(num_of_coll->value()));
}

void Game::playCb(Fl_Widget* widg, void* val)
{
	widg->window()->hide();
}

void Game::setPlayers(int n_of_players)
{
	if (n_of_players > 0)
		for (int i = 1; i <= n_of_players; i++)
			players.push_back(Player(i));
	else
		isRunning = false;
}

void Game::setCards(int row, int col)
{
	if (row * col > 0 || row * col % 2 == 0)
	{
		num_of_rows = row;
		num_of_cols = col;
	}
	else
		isRunning = false;
}

void Game::eventHandler(Player* p)
{
	SDL_Event ev;
	SDL_Point mouse_position;

	while (isRunning && SDL_WaitEvent(&ev) && p->isPlaying)
	{
		switch (ev.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				p->pick_card(cards[findCardPos(&mouse_position.y)][findCardPos(&mouse_position.x)]);
				std::cout << "CARD VALUE " <<
					cards[findCardPos(&mouse_position.y)][findCardPos(&mouse_position.x)].card_value << std::endl;
				update(mouse_position);
				p->checkCards();
				
				/*SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
				SDL_Log("Card position: row=%i coll=%i", findCardPos(&mouse_position.y), findCardPos(&mouse_position.x));
				p->selected_cards.insert(
					p->selected_cards.begin(),
					cards[findCardPos(&mouse_position.y)][findCardPos(&mouse_position.x)]
					.card_value);*/
		}
	}
	p->selected_cards.clear();
}

void Game::render()
{
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);
}

void Game::update(SDL_Point point) 
{
	int r = findCardPos(&point.y);
	int c = findCardPos(&point.x);
	std::cout << r << std::endl;
	std::cout << c << std::endl;

	if(SDL_PointInRect(&point, &cards[r][c].card_rect))
	{
		std::cout << "TRUE" << std::endl;
		SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
		SDL_RenderFillRect(rend, &cards[r][c].card_rect);
		SDL_RenderPresent(rend);
	}
	else
	{
		std::cout << "FALSE" << std::endl;
		
	}
	
}

int Game::findCardPos(int* a) 
{
	return (*a - 50) / 100;
}

void Game::cleanup()
{
	Game::~Game();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
}