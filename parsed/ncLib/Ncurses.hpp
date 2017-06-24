#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <ncurses.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include "../inc/libs.hpp"

class ncurses : public dynamic_libs {

	private:

		// char 			partchar;
		// char 			wall;
		// char 			lunch;

		int 			max_width;
        int 			max_height;
        int 			stdscr_x;
        int 			stdscr_y;

	public:

		ncurses();
		ncurses(unsigned int tmp_x, unsigned int tmp_y);
		ncurses(ncurses const &src);
		~ncurses();

		ncurses &operator=(ncurses const &src);

		bool		Init(unsigned int &maxX, unsigned int &maxY);
		// void 		Render(char **map, unsigned int &score, bool &pause);
		// int 		Input(int &dir, int &lib);

		// void    Init();
		void    	Render(char **map, unsigned int &score, bool &pause);
        //void    Render();
        int    	Input(char &direction, int &lib);
};

#endif
