#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include "Input.h"
#include "Player.h"
#include <vector>

class Game 
{
	
	public:
		Game();
		~Game();
		int getInput(const char* display_text);
		void setPlayers();
		void setCards();
		void setup(const char* title, int x_pos, int y_pos, int w, int h, bool fullscreen);
		void eventHandler();
		void update();
		void render();
		void cleanup();
		bool isRunning;
		//int num_of_players;
		int num_of_cards;
		std::vector<Player> num_of_players;

	private:
		SDL_Window* window;
		SDL_Renderer* rend;

};