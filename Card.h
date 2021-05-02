#include <SDL.h>
#pragma once

class Card 
{
	public:
		Card(int r, int c);
		Card();
		~Card();
		int row;
		int col;
		//static const int card_h;
		//static const int card_w;
		int card_value;
		bool is_open;
		SDL_Rect card_rect;
		void select(SDL_Point* point);
		void flip();


	//private:
	//	int card_value;
	//	int row;
	//	int col;
};