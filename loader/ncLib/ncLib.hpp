#ifndef NCLIB_HPP
#define NCLIB_HPP

#include <ncurses.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include "../inc/libs.hpp"

class ncurses : public dynamic_libs {

	private:


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

		bool		Init();
		void    	Render();
        int    	Input(int &lib);
};

#endif
