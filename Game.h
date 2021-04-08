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
		void set_players();
		void setup(const char* title, int x_pos, int y_pos, int w, int h, bool fullscreen);
		void eventHandler();
		void update();
		void render();
		void cleanup();
		bool isRunning;

	private:
		SDL_Window* window;
		SDL_Renderer* rend;
		int num_of_players;

};