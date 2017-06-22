#include "test.hpp"

snakepart::snakepart(int col, int row) {
	x = col;
	y = row;
}

snakepart::snakepart() {
	x = 0;
	y = 0;
}

snakeclass::snakeclass(int x, int y) {
	

	playerCube.x = x;
	playerCube.y = y;
	playerCube.w = 20;
	playerCube.h = 20;

	for(int i = 0; i < 5; i++)
		snake.push_back(snakepart(playerCube.x + i * 20, playerCube.y));
	//points=0;

	delay = 200;
	get = false;
	direction = 'l';
	srand(time(0));
	putfood();

	Render();
}

snakeclass::~snakeclass() {
	SDL_Quit();
}

void snakeclass::putfood() {
	while(1) {
		int tmpx = (rand() % (screenWidth / 20)) * 20;
		int tmpy = (rand() % (screenHeight / 20)) * 20;
/*
		for(unsigned long i = 0; i < snake.size(); i++)
			if(snake[i].x == tmpx && snake[i].y == tmpy)
				continue;
*/				
		if(tmpx >= screenWidth || tmpy >= screenHeight)
			continue;
		food.x = tmpx;
		food.y = tmpy;
		food.w = 20;
		food.h = 20;
		break;
	}
	Render(); //need to pass coordinates to render function
}

bool snakeclass::collision() {
	if(snake[0].x == 0 || snake[0].x == screenWidth - 20 || snake[0].y == 0 || snake[0].y == screenHeight - 20)
		return 1;
/*
	for(unsigned long i = 2; i < snake.size(); i++)
		if(snake[0].x == snake[i].x && snake[i].y == snake[0].y)
			return true;
	*/
	if(snake[0].x == food.x && snake[0].y == food.y) {
		get = true;
		putfood();
	}
	
	else
		get=false;
	return false;
}

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
	if(!get) {
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

bool snakeclass::InitSDL() {
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool snakeclass::CreateWindow() {
	window = SDL_CreateWindow( "Server", posX, posY, screenWidth, screenHeight, 0 );

	if ( window == nullptr ) {
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}
	return true;
}

bool snakeclass::CreateRenderer() {
	renderer = SDL_CreateRenderer( window, -1, 0 );

	if ( renderer == nullptr ) {
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}
	return true;
}

void snakeclass::SetupRenderer() {
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize( renderer, screenWidth, screenHeight );
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
}

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