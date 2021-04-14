#include "Game.h"
#include <vector>

int main(int argc, char* argv[])
{
	Game *game = new Game();

	game->set_cards();
	if (game->num_of_cards % 2 == 0)
		game->set_players();

	if (game->num_of_players.size() > 0)
		game->setup("Memo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);

	while (game->isRunning)
	{
		/*for (Player &p : all_players)
		{
			game->eventHandler();
			game->update();
			game->render();
		}*/
		game->eventHandler();
		game->update();
		game->render();
	}

	game->cleanup();
	return 0;
}