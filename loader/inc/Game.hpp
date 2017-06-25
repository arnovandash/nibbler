#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <dlfcn.h>
#include <curses.h>
#include <stdlib.h>
#include <term.h>
#include "libs.hpp"


struct Part{
	unsigned int     x;
	unsigned int     y;
	Part(unsigned int col, unsigned int row);
	Part();
};

class Game
{
	private:
		dynamic_libs *	lib;

		void *		GLibHandler;
		bool		gameRun;
		int		current_lib;
		bool		lib_closed;

		unsigned int	delay;
		int		score;
		bool		eat;
		char		direction;
		unsigned int	screenWidth;
		unsigned int	screenHeight;

		Part		food;
		std::vector<Part>	snake;

	public:
		Game(void);
		Game(unsigned int width, unsigned int height);
		Game(Game const &src);
		~Game(void);

		Game &operator=(Game const &obj);

		void		runGame();
		void		initialise();
		void		parseKey(int key);
		void		load_lib(std::string const &lib_path);
		void		close_lib();

		void		putfood();
		bool		collision();
		void		movesnake();

		//void		LoadMap();
		//void		mapSymbols();
		//void		create_snake();
		//void		change_lib(int &ret_tmp);
};
