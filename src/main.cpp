// Local includes
#include "engine/Game.h"
#include "game/Config.h"

// SDL includes

// std includes
#include <time.h>

int main(int argc, char* args[])
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Game& game = Game::getInstance("Snake 2D", SCREEN_WIDTH, SCREEN_HEIGHT);
	game.run();

	return 0;
}
