#include "Game.h"

int main(int argv, char** argc)
{
	Game* game = new Game();
	game->Start();

	delete game;
	return 0;
}