#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <ncurses.h>

#include <iostream>
#include <vector>
#include <cstdlib>

struct snakepart{
	int x;
	int y;
	snakepart(int col, int row);
	snakepart();
};

class snakeclass{
	
	int 		score;
	int			delay;
	bool 		eat;
	char 		direction;
	int 		screenWidth;
	int 		screenHeight;

	snakepart 	food;
	std::vector<snakepart> snake;

///////////////////////////////////
	char 		partchar;
	char 		wall;
	char 		lunch;
///////////////////////////////////

	void putfood();
	bool collision();
	void movesnake();

	public:
	snakeclass();
	~snakeclass();

	void RunGame();
};

#endif
