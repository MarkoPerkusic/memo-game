#include "Game.h"

int main(int argc, char* argv[])
{
	Game *game = new Game();

	game->getInput();
	if(game->isRunning)
		game->setup("Memo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);

	SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 255);
	SDL_RenderClear(game->rend);

	for (int c = 0; c < game->num_of_rows; c++)
	{
		game->cards.push_back(std::vector<Card>());
		for (int r = 0; r < game->num_of_cols; r++)
		{
			Card card(r, c);
			game->cards[c].push_back(card);

			SDL_SetRenderDrawColor(game->rend, 255, 0, 0, 255);
			SDL_RenderFillRect(game->rend, &card.card_rect);
			SDL_RenderPresent(game->rend);
		}
	}

	for (Player& p : game->players)
	{
		while (game->isRunning)
		{
			//p.pick_card();
			//std::cout << &p << std::endl;
			game->eventHandler();

			//game->update();
			//game->render();

		}
	}

	game->cleanup();
	return 0;
}