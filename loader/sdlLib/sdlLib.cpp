#include "sdlLib.hpp"

extern "C" dynamic_libs *create() {
	return (new sdl);
}

extern "C" void destroy(dynamic_libs *obj) {
	delete obj;
}

sdl::sdl() {
	max_width = 0;
	max_height = 0;
	stdscr_x = 0;
	stdscr_y = 0;
}

sdl::sdl(unsigned int tmp_x, unsigned int tmp_y) {
	max_width = tmp_x;
	max_height = tmp_y;
}

sdl::sdl(sdl const &src) {
	*this = src;
}

sdl::~sdl() {
	SDL_Quit();
}

sdl &sdl::operator=(sdl const &src)
{
	max_height = src.max_height;
	max_width = src.max_width;

	return (*this);
}

bool	sdl::Init() {

////////////// Remove ///////////////
	unsigned int posX = 50;
	unsigned int posY = 50;
	unsigned int screenWidth = 100;
	unsigned int screenHeight = 100;
///////////////////////////////////////

	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}
	window = SDL_CreateWindow( "Server", posX, posY, screenWidth, screenHeight, 0 );

	if ( window == nullptr ) {
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}
	renderer = SDL_CreateRenderer( window, -1, 0 );

	if ( renderer == nullptr ) {
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}
//	SDL_RenderSetLogicalSize( renderer, screenWidth, screenHeight );
	SDL_RenderSetLogicalSize( renderer, 30, 30 );
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
	SDL_Delay(3000);
	return (false);
}

/*
bool	sdl::Init() {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	return (false);
}
*/
void sdl::Render()
{
}

int sdl::Input(int &lib)
{
	int tmp =5;// getch();
	std::cout << tmp << std::endl;
	switch(tmp)
	{
		case 49:
			if (lib != 5)
				return (5);
			break ;
		case 50:
			if (lib != 6)
				return (6);
			break ;
		case 51:
			if (lib != 7)
				return (7);
			break ;
		case 27:
			return (8);
		case 32:
			return (9);
	}
	return (0);
}

