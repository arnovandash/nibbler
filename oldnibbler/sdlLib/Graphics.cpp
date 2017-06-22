#include <iostream>
#include "Graphics.hpp"
#include "../src/Snake.hpp"
//#include "sdl_check.hpp"
extern "C" {
	#include <unistd.h>
}
//============= All the ncurses functions we'd usually use====//

Graphics::Graphics(const Snake & s) : _snake(s) {
	
	SDL_Surface* screenSurface = NULL;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else {
		_window = SDL_CreateWindow(
				"Nibbler",
				_posX,
				_posY,
				_snake.map->width * 20,
				_snake.map->height * 20,
				SDL_WINDOW_OPENGL
				);
		SDL_Delay(3000);
		if( _window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else {
			screenSurface = SDL_GetWindowSurface( _window );
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			SDL_UpdateWindowSurface( _window );
			SDL_Delay( 2000 );
		}
	}
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void	Graphics::update(void) {
	/*
	   auto oldTick = SDL_GetTicks();
	   for (auto done = false; !done;) {
	   SDL_Event e;
	   if (SDL_PollEvent(&e))
	   {
	   switch (e.type)
	   {
	   case SDL_KEYDOWN:
	   {
	   switch (e.key.keysym.sym)
	   {
	   case SDLK_UP:
	   graphicsLib_action = UP;
	   case SDLK_DOWN:
	   graphicLib_action = DOWN;
	   case SDLK_LEFT:
	   graphicLib_action = LEFT;
	   case SDLK_RIGHT:
	   graphicLib_action = RIGHT;
	   case SDLK_1:
	   graphicsLib_action = LIB1;
	   case SDLK_3:
	   graphicLib_action = LIB3;
	   }
	   }
	   break;
	   case SDL_QUIT:
	   done = true;
	   break;
	   }
	   }
	   SDL_SetRenderDrawColor(renderer, 0x00, 0x7f, 0x00, 0xff);
	   SDL_RenderClear(renderer);
	   auto currentTick = SDL_GetTicks();
	   for (auto t = oldTick; t < currentTick; ++t)
	   if (!tick())
	   return 1;
	   oldTick = currentTick;
	   draw();
	   SDL_RenderPresent(renderer);
	//############# not implemented yet ######################//

	if (ch == 50)
	graphicsLib_action = LIB2;
	if (ch == 51)
	graphicsLib_action = LIB3;

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
*/
}
//========= Uses the IGraphics interface and instanciates the selected lib ======//

IGraphics *	graphicsLib_instantiate(const Snake & s) {
	return new Graphics(s);
}
//=========== Deletes the instanciated Lib ==============//

void		graphicsLib_uninstantiate(IGraphics * g) {
	delete g;
}