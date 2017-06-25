#include "../inc/Game.hpp"
#include <iostream>

int main(void) {
	unsigned int 		height;
	unsigned int 		width;
	
	Game game;

	height = 30;
	width = 30;
	game.initialise();//width, height);
	game.runGame();

	return 0;
}
