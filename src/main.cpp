// Local includes
#include "Game.h"

// SDL includes

// std includes

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[])
{
	Game& game = Game::getInstance("Snake 2D", SCREEN_WIDTH, SCREEN_HEIGHT);
	game.run();

	return 0;
}
