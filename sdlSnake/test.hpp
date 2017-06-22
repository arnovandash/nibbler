#ifndef TEST_HPP
#define TEST_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>

struct snakepart{
	int     x;
    int     y;
	snakepart(int col,int row);
	snakepart();
};

class snakeclass {

public:
    int             posX;
    int             posY;
    int             screenWidth;
    int             screenHeight;
    int             delay;
    int             points;
    char            direction;
	bool            get;

    //snakepart       food;
	std::vector<snakepart *> snake;

    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_Rect        playerCube;
    SDL_Rect        food;

    bool            InitEverything();
    bool            InitSDL();
    bool            CreateWindow();
    bool            CreateRenderer();
    void            SetupRenderer();

    void            Render();

    void            putfood();
	bool            collision();
	void            movesnake();



    //snakeclass();
    snakeclass(int x, int y);
	~snakeclass();

    void RunGame();

};

#endif