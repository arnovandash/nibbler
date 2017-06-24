#include "Sdl.hpp"

void snakeclass::movesnake() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT:
					if(direction != 'r')
						direction='l';
					break;
				case SDLK_UP:
					if(direction !='d')
						direction ='u';
					break;
				case SDLK_DOWN:
					if(direction != 'u')
						direction='d';
					break;
				case SDLK_RIGHT:
					if(direction != 'l')
						direction='r';
					break;
				case SDLK_ESCAPE:
					direction = 'q';
					break;
			}
		}
		else if(event.type == SDL_QUIT)
			direction='q';
	}
	if(!eat) {
		Render();
		snake.pop_back();
	}
	

	if(direction=='l')
		snake.insert(snake.begin(), snakepart(snake[0].x - 20, snake[0].y));
	else if(direction=='r')
		snake.insert(snake.begin(),snakepart(snake[0].x + 20,snake[0].y));
	else if(direction=='u')
		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y - 20));
	else if(direction=='d')
		snake.insert(snake.begin(),snakepart(snake[0].x, snake[0].y + 20));

	Render();
}

void snakeclass::Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &food);
	for (unsigned int i = 0; i < snake.size(); i++) {
		playerCube.x = snake[i].x;
		playerCube.y = snake[i].y;
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &playerCube);
	}
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderPresent(renderer);
	
}

bool snakeclass::InitEverything() {
	if (!InitSDL())
		return false;
	if (!CreateWindow())
		return false;
	if (!CreateRenderer())
		return false;
	SetupRenderer();

	putfood();
	return true;
}
//////////////////////////////////////////////////////////////

bool	sdl::Init() {
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
}


/////////////////////////////////////////////////////////////////
void snakeclass::RunGame() {
	bool loop = true;

	while(loop) {
		if(collision()) {
			std::cout << "game over" << std::endl;
			break;
		}
		movesnake();
		if(direction == 'q')
			break;
		SDL_Delay(delay);
	}
}
