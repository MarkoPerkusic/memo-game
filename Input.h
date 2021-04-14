#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

class Input
{
	public:
		Input();
		~Input();
		void inputHandler();
		void inputWindow(const char* text);
		int inputShow();
		
	private:
		std::string input;
		void applyText(TTF_Font* font, SDL_Color font_col, SDL_Rect rect, SDL_Renderer* rend, const char* text);
};