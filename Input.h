#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

class Input
{
	public:
		Input();
		~Input();
		void handle_input();
		void input_window(const char* text);
		int show_input();
		
	private:
		std::string input;
		/*void apply_text(TTF_Font* font, SDL_Color font_col, SDL_Rect rect, SDL_Renderer* rend, const char* text);*/
};