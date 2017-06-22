#include <iostream>
#include "Snake.hpp"
#include "Player.hpp" 

static int parseInt() {
	int i;

	while (!(std::cin >> i) || i < 0) {
		std::cout << "Bad input - try again: ";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	return i;
}

static std::string parseLib() {
	std::string lib;

	while (lib.empty()) {
		std::cout << ": ";
		std::getline(std::cin, lib, '\n');
		std::cout << std::endl;
	}
	return lib;
}

int main(void) {
	int 		height;
	int 		width;
	std::string	lib;

	Snake snake;
	Player player;

	std::cout << "Enter Height for game screen: ";
	height = parseInt();
	std::cout << "Enter Width for game screen: ";
	width = parseInt();
	std::cout << "Enter library: [path]/[library.so]";
	lib = parseLib();
	snake.loadMap(width, height);
	snake.loadLibrary(lib);
	snake.launch();
	//SCORE NOT WORKING
	//std::cout << "You lost with a score of " << player.score << "." << std::endl;
	return 0;
}
