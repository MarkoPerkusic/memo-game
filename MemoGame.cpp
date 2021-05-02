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
			if (c < 2)
				card.card_value = 1;
			game->cards[c].push_back(card);

			SDL_SetRenderDrawColor(game->rend, 255, 0, 0, 255);
			SDL_RenderFillRect(game->rend, &card.card_rect);
			SDL_RenderPresent(game->rend);
		}
	}

	
	while (game->isRunning)
	{
		for (Player& p : game->players)
		{
			if (!game->isRunning)
				break;
			//p.pick_card();
			std::cout << p.getName() << std::endl;
			game->eventHandler(&p);
			//std::cout << "CARD " << p.selected_cards[0] << std::endl;
			//game->update();
			//game->render();
		}
	}

	game->cleanup();
	return 0;
}