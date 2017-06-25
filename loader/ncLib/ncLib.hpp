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
		int 			screenWidth;
		int 			screenHeight;

		char			partchar;
		char			wall;
		char			lunch;

	public:

		ncurses();
		ncurses(unsigned int tmp_x, unsigned int tmp_y);
		ncurses(ncurses const &src);
		~ncurses();

		ncurses &operator=(ncurses const &src);

		bool		Init(int Width, int Height);
		int    	Render(int foodX, int foodY, std::vector<Part> snake);
		int    	Input(int &lib);
};

#endif
