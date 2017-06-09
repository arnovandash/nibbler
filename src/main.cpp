#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include "Window.hpp"
#include "snake.hpp"

void librarySelector(int lib) {
	std::cout << "in lib selector" << std::endl;
	
	switch(lib) {
		case 1:
			std::cout << "NCurses lib selected" << std::endl;
			Ngame();
            break;
		case 2:
			std::cout << "openGL lib selected" << std::endl;
			break;
		case 3:
			std::cout << "other lib selected" << std::endl;
			break;
	}
}

int main(void) {
	int height;
	int width;
	int	lib;

	std::cout << "Enter Height for game screen: ";
	
	while (!(std::cin >> height) || height < 0) {
    	std::cout << "Bad input - try again: ";
    	std::cin.clear();
    	std::cin.ignore(INT_MAX, '\n');
	}
	
	std::cout << "Enter Width for game screen: ";
	while (!(std::cin >> width) || width < 0) {
    	std::cout << "Bad input - try again: ";
    	std::cin.clear();
    	std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "Enter library 1, 2 or 3: ";
	lib = 0;
	while (lib < 1 || lib > 3 || std::cin.peek() != '\n') {
    	std::cin >> lib;
		if (std::cin.fail()) {
			std::cout << "Bad input - try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			lib = 0;
		}
	}

	std::cout << "Testing output values captured correctly: " << std::endl;
	std::cout << "height = " << height << std::endl;
	std::cout << "width = " << width << std::endl;
	std::cout << "lib = " << lib << std::endl;

	librarySelector(lib);

	return 0;
}
