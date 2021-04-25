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

	play_but->callback((Fl_Callback*)play_cb, num_of_players);
	win->show();
	Fl::run();

	std::cout << atoi(num_of_players->value()) << std::endl;
	std::cout << num_of_players->value() << std::endl;
	std::cout << atoi(num_of_rows->value()) * atoi(num_of_coll->value()) << std::endl;

	setPlayers(atoi(num_of_players->value()));
	setCards(atoi(num_of_rows->value()), atoi(num_of_coll->value()));
}

void Game::play_cb(Fl_Widget* widg, void* val)
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
		//cards.resize(row, std::vector<Card> (col));
	}
	else
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
		case SDL_MOUSEBUTTONDOWN:
			/*std::cout << ev.button.x << std::endl;
			std::cout << ev.button.y << std::endl;
			std::cout << "---------" << std::endl;*/
			SDL_Point mouse_position;
			SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

			SDL_Log("Mouse position: x=%i y=%i", mouse_position.x, mouse_position.y);
			SDL_Log("Card position: x=%i y=%i", findCardPos(&mouse_position.x), findCardPos(&mouse_position.y));
			
			update();

		default:;
	}
}

void Game::render()
{
	int SDL_RenderClear(SDL_Renderer*);
	void SDL_RenderPresent(SDL_Renderer*);
	
	//SDL_RenderClear(rend);
	//SDL_RenderPresent(rend);
}

void Game::update() 
{
	SDL_Rect r;
	r.x = 50;
	r.y = 50;
	r.w = 50;
	r.h = 80;

	SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
	SDL_RenderFillRect(rend, &r);
	SDL_RenderPresent(rend);
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