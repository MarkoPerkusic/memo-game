#include "Input.h"
#include <iostream>

const int FONT_SIZE = 25;
const int W_WIDTH = 450;
const int W_HEIGHT = 200;

Input::Input() 
{
	input = "";
}

Input::~Input() {}

void Input::inputWindow(const char* text)
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
	
	Input::applyText(font, font_col, {50, 50, 100, 100}, r, text);

	inputHandler();

	Input::applyText(font, font_col, { 150, 100, 100, 100 }, r, input.c_str());

	SDL_Delay(500);
	TTF_CloseFont(font);
	SDL_DestroyWindow(w);
}

void Input::applyText(TTF_Font* font, SDL_Color font_col, SDL_Rect rect, SDL_Renderer* rend, const char* text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, font_col);
	SDL_Texture* message = SDL_CreateTextureFromSurface(rend, surface);
	SDL_QueryTexture(message, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(rend, message, NULL, &rect);
	SDL_RenderPresent(rend);
}

void Input::inputHandler()
{
	bool running = true;
	SDL_StartTextInput();

		SDL_Event ev;
		
		while (running) {
			SDL_Event ev;
			while (SDL_PollEvent(&ev))
			{
				if (ev.key.state >= '0' && ev.key.state <= '9')
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
}

int Input::inputShow()
{
	return std::stoi(input);
}