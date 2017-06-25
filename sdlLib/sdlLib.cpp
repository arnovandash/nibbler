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

bool	sdl::Init(int Width, int Height) {
	screenWidth = Width * 20;
	screenHeight = Height * 20;
	int	posX = 10;
	int	posY = 10;
	food.w = 20;
	food.h = 20;
	playerCube.w = 20;
	playerCube.h = 20;


	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}
	window = SDL_CreateWindow( "Server", posX, posY, screenWidth, screenHeight, 0 );

	if ( window == nullptr ) {
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	if ( renderer == nullptr ) {
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
	return (false);
}

int sdl::Render(int foodX, int foodY, std::vector<Part> snake)
{
	food.x = foodX * 20;
	food.y = foodY * 20;
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &food);
	for (unsigned int i = 0; i < snake.size(); i++) {
		playerCube.x = snake[i].x * 20;
		playerCube.y = snake[i].y * 20;
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &playerCube);
	}
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderPresent(renderer);
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym)
			{
				case SDLK_UP:
					return (1);
					break;
				case SDLK_DOWN:
					return (2);
					break;
				case SDLK_LEFT:
					return (3);
					break;
				case SDLK_RIGHT:
					return (4);
					break;
				case SDLK_1:
					return(5);
					break;
				case SDLK_3:
					return(7);
					break;
				case SDLK_ESCAPE:
					return(8);
					break;
				case SDLK_SPACE:
					return(9);
					break;
			}
		}
		else if(event.type == SDL_QUIT)
			return(8);
	}
	return (0);
}
