#include "Card.h"
#include <iostream>

Card::Card()
{
	is_open = false;
}

Card::Card(int r, int c)
{
	is_open = false;
	card_value = 0;
	row = r;
	col = c;
	card_rect.x = 50 + r * 100;
	card_rect.y = 50 + c * 100;
	card_rect.w = 50;
	card_rect.h = 80;
}

Card::~Card() {}

void Card::select(SDL_Point* point)
{
	if (SDL_PointInRect(point, &card_rect) == SDL_TRUE)
		is_open = true;
}

void Card::close()
{
	is_open = false;
}

