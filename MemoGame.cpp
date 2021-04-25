#include "Game.h"

int main(int argc, char* argv[])
{
	Game *game = new Game();

	game->getInput();
	if(game->isRunning)
		game->setup("Memo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);

	SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 255);
	SDL_RenderClear(game->rend);

	for (int j = 0; j < game->num_of_rows; j++)
		for (int k = 0; k < game->num_of_cols; k++)
		{
			game->cards.push_back(std::vector<Card>());
			Card card(j, k);
			game->cards[j].push_back(card);

			SDL_SetRenderDrawColor(game->rend, 255, 0, 0, 255);
			SDL_RenderFillRect(game->rend, &card.card_rect);
			SDL_RenderPresent(game->rend);
		}

	while (game->isRunning)
	{
		for (Player &p : game->players)
		{
			//p.pick_card();
			game->eventHandler();
			//game->update();
			//game->render();

		}
	}

	game->cleanup();
	return 0;
}