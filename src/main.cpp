#include "../inc/Game.hpp"
#include <iostream>

static int parseInt() {
	int i;

	while (!(std::cin >> i) || i < 30 || i > 50) {
		std::cout << "Bad input - try again: ";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	return i;
}

int main(void) {
	unsigned int 		height;
	unsigned int 		width;
	
	std::cout << "Enter Height for game screen: 30 - 50 -> ";
	height = parseInt();
	std::cout << "Enter Width for game screen: 30 - 50 -> ";
	width = parseInt();
	Game game(width, height);
	
	game.initialise();
	game.runGame();

	return 0;
}