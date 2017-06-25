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
		int 			screenWidth;
		int 			screenHeight;
		SDL_Rect		food;
		SDL_Rect		playerCube;

	public:

    SDL_Window*     window;
    SDL_Renderer*   renderer;


		sdl();
		sdl(unsigned int tmp_x, unsigned int tmp_y);
		sdl(sdl const &src);
		~sdl();

		sdl &operator=(sdl const &src);

		bool		Init(int Width, int Height);
		int    	Render(int foodX, int foodY);
};

#endif
