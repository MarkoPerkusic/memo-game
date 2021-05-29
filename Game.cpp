#include "Game.h"

Game::Game() 
{
	isRunning = true;
	window = nullptr;
	rend = nullptr;
}
Game::~Game() {}

void Game::setup(const char* title, int x_pos, int y_pos, int w, int h) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		isRunning = false;

	window = SDL_CreateWindow(title, x_pos, y_pos, w, h, 0);
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

/*
* Return the value that is randomly selected
* from the deck which has all the values that
* cards can have
*/
int Game::shuffleCardValues()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle(card_values_deck.begin(), card_values_deck.end(), std::default_random_engine(seed));
	int value = card_values_deck.front();
	card_values_deck.erase(card_values_deck.begin());
	return value;
}

void Game::setCards(int row, int col)
{
	if (row * col > 0 || row * col % 2 == 0)
	{
		num_of_rows = row;
		num_of_cols = col;

		//At this stage, the max number of points in game
		available_points = row * col / 2;
		
		//Crete card value number that the pair of cards will have in order to be matched
		//1 number is assigned to 2 cards, therefore card max value is equal to max available points
		for (int i = 1; i <= available_points; i++)
			card_values_deck.push_back(i);

		//Duplicate cards value numbers so that each card will have randomly assigned number from deck
		card_values_deck.insert(card_values_deck.end(), 
				card_values_deck.begin(), card_values_deck.end());
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
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

				//Limit the click on the area where the cards are displayed
				if (mouse_position.x >= 100 && mouse_position.x <= 150 + 100 * (num_of_cols-1) &&
					mouse_position.y >= 70 && mouse_position.y <= 150 + 100 * (num_of_rows-1))
				{
					//Check if the click was on the card
					if (update(mouse_position))
					{
						std::cout << "CARD SELECTED\n" << available_points << std::endl;
						p->selectCard(&cards[findCardPos(&mouse_position.y)][findCardPos(&mouse_position.x)]);
						if (p->selected_cards.size() == 2)
							p->checkCards();
						//In case of match, reduce available points
						if (p->isPlaying && p->selected_cards.size() == 2)
						{
							printf("\nLOWERING AVAIL POINTS");
							available_points--;
							std::cout << "\n" << available_points << std::endl;
							p->selected_cards.clear();
						}
						//In case of the wrong cards, close them back
						if (!p->isPlaying && p->selected_cards.size() == 2)
						{
							printf("\nLOSING TURN!");
							update(*p->selected_cards[0], *p->selected_cards[1]);
							p->closeCards();
							displayPlayers(*p, 0, 0, 0);
						}
					}
					else
						std::cout << "CARD NOT SELECTED\n" << available_points << std::endl;
					
					if (available_points == 0)
						isRunning = false;
				}
				

			/*case SDL_MOUSEWHEEL:
				if (ev.wheel.y > 0)
				{
					std::cout << ev.wheel.y << std::endl;
				}
				else if (ev.wheel.y < 0)
				{
					std::cout << ev.wheel.y << std::endl;
				}
				if (ev.wheel.x > 0)
				{
					std::cout << ev.wheel.x << std::endl;
				}
				else if (ev.wheel.x < 0)
				{
					std::cout << ev.wheel.x << std::endl;
				}*/
		}
	}
}

void Game::render()
{
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);
}

void Game::update(Card card1, Card card2)
{
	SDL_Delay(1000);
	const SDL_Rect rects[] = { card2.card_rect, card1.card_rect };
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderFillRects(rend, rects, 2);
	SDL_RenderPresent(rend);
}

bool Game::update(SDL_Point point) 
{
	int r = findCardPos(&point.y);
	int c = findCardPos(&point.x);

	if (SDL_PointInRect(&point, &cards[r][c].card_rect) && !cards[r][c].is_open)
	{
		SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
		SDL_RenderFillRect(rend, &cards[r][c].card_rect);
		SDL_RenderPresent(rend);
		cards[r][c].is_open = true;
		return true;
	}
	else
		return false;
	
}

void Game::showResults(std::vector<Player> scores)
{
	//Player name and score
	std::string text_to_print = "";
	std::string text_stlye = "";

	//First player will always have higest score
	int top_result = scores[0].score;

	for (Player& i : scores)
	{
		std::string name_and_score = i.getName() + " : " + std::to_string(i.score);
		text_to_print.append("\n" + name_and_score);
		
		//Mark the player if it has a top result
		if (i.score == top_result)
		{
			text_to_print.append("\tWINNER");
			//Increase size by 8 because of \tWINNER
			text_stlye.append(std::string(name_and_score.size() + 8, 'A') + "\n");
		}
	}
	
	Fl_Text_Display::Style_Table_Entry style[] = { FL_DARK_YELLOW, FL_COURIER, 19 };
	Fl_Window* win = new Fl_Window(350, 200);
	Fl_Text_Buffer* text_buff = new Fl_Text_Buffer();
	Fl_Text_Buffer* style_buff = new Fl_Text_Buffer();
	Fl_Text_Display* disp = new Fl_Text_Display(40, 20, 300, 150, "PLAYERS RANKINGS");
	
	disp->buffer(text_buff);
	disp->highlight_data(style_buff, style, 1, 'A', 0, 0);
	text_buff->text(text_to_print.c_str());
	style_buff->text(text_stlye.c_str());
	
	win->resizable(*disp);
	win->show();
	Fl::run();
}

void Game::displayPlayers(Player p, int r, int g, int b)
{
	if (TTF_Init() == 0)
	{
		//Setup font
		TTF_Font* font = TTF_OpenFont("arial.ttf", 20);
		SDL_Color font_col = { 0, 255, 0 };

		//Setup frame for a player that is currently playing
		SDL_SetRenderDrawColor(rend, r, g, b, 1);
		
		//Get ordinal number of the player, player_id
		//int p_id = stoi(p.getName().substr(6, p.getName().length()));

		//Move the rect that represents the frame on x position by its width, 80 
		SDL_Rect rect = { p.x_pos(), p.y_pos(), 80, 30 };
		SDL_RenderFillRect(rend, &rect);

		SDL_Surface* surface = TTF_RenderText_Solid(font, p.getName().c_str(), font_col);
		SDL_Texture* message = SDL_CreateTextureFromSurface(rend, surface);
		SDL_QueryTexture(message, NULL, NULL, &rect.w, &rect.h);
		SDL_RenderCopy(rend, message, NULL, &rect);
		SDL_RenderPresent(rend);
	}
}

bool Game::playAgain()
{
	switch (fl_choice("What to play again?", "YES", "NO", 0)) 
	{
	case 0:
		return true;
	case 1:
		return false;
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