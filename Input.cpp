#include "Input.h"
#include <iostream>
#include <string>

const int FONT_SIZE = 25;
const int W_WIDTH = 400;
const int W_HEIGHT = 200;

Input::Input() 
{
	input = "";
};
Input::~Input() {};

void Input::input_window(const char* text)
{
	SDL_Window* w = SDL_CreateWindow("How many", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		W_WIDTH, W_HEIGHT, false);
	SDL_Renderer* r = SDL_CreateRenderer(w, -1, 0);

	if (TTF_Init() != 0)
	{
		Input::~Input();
	};
	
	TTF_Font* font = TTF_OpenFont("arial.ttf", FONT_SIZE);
	SDL_Color font_col { 0, 255, 0 };
	
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, font_col);
	SDL_Texture* message = SDL_CreateTextureFromSurface(r, surface);
	SDL_Rect rect {50, 50, 100, 100};
	SDL_QueryTexture(message, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(r, message, NULL, &rect);
	SDL_RenderPresent(r);

	/*Input::apply_text(font, font_col, {50, 50, 100, 100}, r, text);*/

	handle_input();

	/*Input::apply_text(font, font_col, { 150, 100, 100, 100 }, r, input.c_str());*/
	SDL_Rect rect2 { 150, 100, 100, 100 };
	SDL_Surface* surface2 = TTF_RenderText_Solid(font, input.c_str(), font_col);
	SDL_Texture* message2 = SDL_CreateTextureFromSurface(r, surface2);
	SDL_BlitSurface(surface2, NULL, surface, &rect2);
	SDL_QueryTexture(message2, NULL, NULL, &rect2.w, &rect2.h);
	SDL_RenderCopy(r, message2, NULL, &rect2);
	SDL_RenderPresent(r);

	SDL_Delay(2000);

	TTF_CloseFont(font);
	SDL_DestroyWindow(w);
};

/*void Input::apply_text(TTF_Font* font, SDL_Color font_col, SDL_Rect rect, SDL_Renderer* rend, const char* text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, font_col);
	SDL_Texture* message = SDL_CreateTextureFromSurface(rend, surface);
	SDL_QueryTexture(message, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(rend, message, NULL, &rect);
	SDL_RenderPresent(rend);
};*/

void Input::handle_input()
{
	bool running = true;
	SDL_StartTextInput();

		SDL_Event ev;
		
		while (running) {
			SDL_Event ev;
			while (SDL_PollEvent(&ev))
			{
				if (ev.type == SDL_TEXTINPUT)
				{
					input += ev.text.text;
				}
				else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN)
				{
					if (input == "")
					{
						input = "0";
					}
					running = false;
				}
				else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && input.length() > 0)
				{
					input.pop_back();
				}
				else if (ev.type == SDL_QUIT)
				{
					input = "0";
					running = false;
				}
			}
		}
	SDL_StopTextInput();
};

int Input::show_input() 
{
	return std::stoi(input);
};