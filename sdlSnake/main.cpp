#include "test.hpp"

int main( void ) {
	
	snakeclass s(320, 240);

	s.posX = 500;
    s.posY = 200;
    s.screenWidth = 640;
    s.screenHeight = 480;

	if (!s.InitEverything()){

		std::cout << "Not initialised" << std::endl;
		return -1;
	}

	s.RunGame();
	return 0;

	
}