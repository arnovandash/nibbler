#include <iostream>
#include "Graphics.hpp"
#include "../src/Snake.hpp"

extern "C" {
	#include <curses.h>
	#include <unistd.h>
}
//============= All the ncurses functions we'd usually use====//

Graphics::Graphics(const Snake & s) : _snake(s) {
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	timeout(1);
}

Graphics::~Graphics() {
	endwin();
}

void	Graphics::update(void) {
	clear();
	unsigned	x;
	unsigned	y;

	int ch;

	while ((ch = getch()) != -1) {
		if (ch == 112)
			graphicsLib_action = PAUSE;
		if (ch == 258)
			graphicsLib_action = DOWN;
		if (ch == 259)
			graphicsLib_action = UP;
		if (ch == 260)
			graphicsLib_action = RIGHT;
		if (ch == 261)
			graphicsLib_action = LEFT;
		//############# not implemented yet ######################//
		
		if (ch == 50)
			graphicsLib_action = LIB2;
		/*
		if (ch == 51)
			graphicsLib_action = LIB3;
		*/
	}
	y = 0;

	while (y < _snake.map->height) {
		printw("   ");
		x = 0;
		while (x < _snake.map->width) {
			switch (_snake.map->map[y][x])
			{
				case BLOCK_NONE:
					printw(" ");
					break;
				case BLOCK_WALL:
					printw("#");
					break;
				case BLOCK_FOOD:
					printw("*");
					break;
				case BLOCK_HEAD:
					printw("@");
					break;
				default:
					printw("o");
			}
			printw(" ");
			x++;
		}

		printw("\n");
		y++;
	}

	refresh();
	usleep(50000);
}
//========= Uses the IGraphics interface and instanciates the selected lib ======//

IGraphics *	graphicsLib_instantiate(const Snake & s) {
	return new Graphics(s);
}
//=========== Deletes the instanciated Lib ==============//

void		graphicsLib_uninstantiate(IGraphics * g) {
	delete g;
}
