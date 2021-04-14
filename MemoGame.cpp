#include "Game.h"
#include <vector>

int main(int argc, char* argv[])
{
	Game *game = new Game();

	game->setCards();
	if (game->num_of_cards % 2 == 0)
		game->setPlayers();
	
	if (game->num_of_players.size() > 0)
		game->setup("Memo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);

	while (game->isRunning)
	{
		for (Player &p : game->num_of_players)
		{
			//p.pick_card();
			game->eventHandler();

		}
		//game->eventHandler();
		//game->update();
		//game->render();
	}

	game->cleanup();
	return 0;
}