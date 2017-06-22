#include <iostream>
#include <vector>
#include <cstdlib>
#include <SDL2/SDL.h>
//#include <SDL/SDL_ttf.h>
#ifndef SNAKE_HPP
#define SNAKE_HPP

struct snakepart{
	int x,y;
	snakepart(int col,int row);
	snakepart();
};

class snakeclass{
	int points,del,width,height;
	char direction;
	bool get;
	snakepart food;
	std::vector<snakepart> snake;
	//SDL_Surface* screen; //sdl1.2
	//SDL_Window * screen;
//	TTF_Font* font;

	void drawRect(int x,int y,Uint32 color,int w=10,int h=10);
	void putfood();
	bool collision();
	void movesnake();
	public:
	snakeclass();
	~snakeclass();
	void start();

	///////////////////TESTING///////////////////
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect playerPos;

	bool InitEverything();
	bool InitSDL();
	bool CreateWindow();
	bool CreateRenderer();
	void SetupRenderer();

	void Render();
	void RunGame();
};

#endif
