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
	SDL_DestroyWindow(window);
	SDL_Quit();
}

sdl &sdl::operator=(sdl const &src)
{
	max_height = src.max_height;
	max_width = src.max_width;

	return (*this);
}

bool	sdl::Init() {


	/////////////tmp////////////

	int	posX = 10;
	int	posY = 10;
	int	screenWidth = 300;
	int	screenHeight = 300;

	////////////////////////////////


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
	return (false);
}

int sdl::Render()
{
	//	int key = getch();
	std::cout << "Running.. " << std::endl;


	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT:
					//	if(direction != 'r')
					//		direction='l';
					break;
				case SDLK_UP:
					//	if(direction !='d')
					//		direction ='u';
					break;
				case SDLK_DOWN:
					//	if(direction != 'u')
					//		direction='d';
					break;
				case SDLK_RIGHT:
					//	if(direction != 'l')
					//		direction='r';
					break;
				case SDLK_1:
					return(5);
					break;
				case SDLK_ESCAPE:
					return(8);
					break;
			}
		}
		else if(event.type == SDL_QUIT)
			return(8);
	}

	/*
	   switch(key)
	   {
	   case 50:// "2" switch lib
	   return (6);
	   break;
	   case 51:// "3" switch lib
	   return (7);
	   break;
	   case 27: // "ESC" quit
	   return (8);
	   break;
	   }
	 */
	return (0);
}

int sdl::Input(int &lib)
{
			if (lib != 7)
				return (7);
/*
	//	int tmp = getch();
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
*/
	return (0);
}

