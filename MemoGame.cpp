#include "Game.h"


int main(int argc, char* argv[])
{
	Game *game = new Game();

	game->getInput();
	if(game->isRunning)
		game->setup("Memo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600);

	int max_points = game->available_points;

	SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 255);

	for (int c = 0; c < game->num_of_rows; c++)
	{
		game->cards.push_back(std::vector<Card>());
		for (int r = 0; r < game->num_of_cols; r++)
		{
			Card card(r, c);
			card.card_value = game->shuffleCardValues();
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
			p.isPlaying = true;
			game->eventHandler(&p);

			if (!game->isRunning)
				break;
		}
	}

	for(int i = 0; i <= max_points; i++)
		for (Player& p : game->players)
			if (i == p.score)
				game->scoreboard.insert(game->scoreboard.begin(), p);

	game->showResults(game->scoreboard);

	game->cleanup();
	return 0;
}