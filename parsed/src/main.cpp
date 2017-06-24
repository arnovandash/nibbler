#include "../inc/Game.hpp"
#include <iostream>

static int parseInt() {
	int i;

	while (!(std::cin >> i) || i < 0) {
		std::cout << "Bad input - try again: ";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	return i;
}

// static std::string parseLib() {
// 	std::string lib;

// 	while (lib.empty()) {
// 		std::cout << ": ";
// 		std::getline(std::cin, lib, '\n');
// 		std::cout << std::endl;
// 	}
// 	return lib;
// }

int main(void) {
	unsigned int 		height;
	unsigned int 		width;

    Game game;

	std::cout << "Enter Height from 20 to 50 for game screen: ";
	height = parseInt();
	std::cout << "Enter Width from 20 to 50 forgame screen: ";
	width = parseInt();
    game.initialise(width, height);
    game.RunGame();

	return 0;
}