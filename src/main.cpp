// Local includes
#include "engine/Game.h"
#include "game/Config.h"

// SDL includes

// std includes

int main(int argc, char* args[])
{
	Game& game = Game::getInstance("Snake 2D", SCREEN_WIDTH, SCREEN_HEIGHT);
	game.run();

	return 0;
}
