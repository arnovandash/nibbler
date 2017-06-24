#ifndef SDLLIB_HPP
#define SDLLIB_HPP

#include <SDL.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include "../inc/libs.hpp"

class sdl : public dynamic_libs {

	private:


		int 			max_width;
		int 			max_height;
		int 			stdscr_x;
		int 			stdscr_y;

	public:

    SDL_Window*     window;
    SDL_Renderer*   renderer;


		sdl();
		sdl(unsigned int tmp_x, unsigned int tmp_y);
		sdl(sdl const &src);
		~sdl();

		sdl &operator=(sdl const &src);

		bool		Init();
		void    	Render();
		int    	Input(int &lib);
};

#endif
