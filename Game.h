#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include "Input.h"

class Game 
{
	
	public:
		Game();
		~Game();
		int get_input(const char* display_text);
		void set_players();
		void set_cards();
		void setup(const char* title, int x_pos, int y_pos, int w, int h, bool fullscreen);
		void eventHandler();
		void update();
		void render();
		void cleanup();
		bool isRunning;
		int num_of_players;
		int num_of_cards;

	private:
		SDL_Window* window;
		SDL_Renderer* rend;

};