#include "Input.h"
#include "Player.h"
#include "Card.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include<FL/Fl.h>
#include<FL/Fl_Box.h>
#include<FL/Fl_Window.h>
#include<FL/Fl_Button.H>
#include<FL/Fl_Int_Input.H>
#include<FL/Fl_Output.H>

#include <vector>
#include <iostream>

class Game 
{
	
	public:
		Game();
		~Game();
		void getInput();
		void setup(const char* title, int x_pos, int y_pos, int w, int h, bool fullscreen);
		void eventHandler();
		void update(SDL_Point point);
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

	private:
		void setPlayers(int players);
		void setCards(int row, int col);
		static void play_cb(Fl_Widget* widg, void* val);

};