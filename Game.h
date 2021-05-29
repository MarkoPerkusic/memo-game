#include "Player.h"
//#include "Card.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include<FL/Fl.h>
#include<FL/Fl_Box.h>
#include<FL/Fl_Window.h>
#include<FL/Fl_Button.H>
#include<FL/Fl_Int_Input.H>
#include<FL/Fl_Output.H>
#include<FL/Fl_Text_Display.H>
#include <FL/fl_ask.H>

#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <map>

class Game 
{
	
	public:
		Game();
		~Game();
		void getInput();
		void setup(const char* title, int x_pos, int y_pos, int w, int h);
		void eventHandler(Player* p);
		bool update(SDL_Point point);
		void update(Card card1, Card card2);
		void render();
		void cleanup();
		bool isRunning;
		int num_of_cols;
		int num_of_rows;
		std::vector<Player> players;
		std::vector< std::vector<Card> > cards;
		SDL_Window* window;
		SDL_Renderer* rend;
		int findCardPos(int* a);
		int available_points;
		std::vector<int> card_values_deck;
		int shuffleCardValues();
		void displayPlayers(Player p, int r, int g, int b);
		std::vector<Player> scoreboard;
		void showResults(std::vector<Player> scores);
		bool playAgain();

	private:
		void setPlayers(int players);
		void setCards(int row, int col);
		static void playCb(Fl_Widget* widg, void* val);

};