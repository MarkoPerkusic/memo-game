#include "Game.h"

int main(int argc, char* argv[])
{
	Game *game = new Game();

	game->set_players();
	if (game->isRunning)
	{
		game->setup("Memo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

		while (game->isRunning)
		{
			game->eventHandler();
			game->update();
			game->render();
		}

		game->cleanup();
	}
	return 0;
}