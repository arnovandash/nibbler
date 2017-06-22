#ifndef TEST_HPP
#define TEST_HPP

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <cstdlib>

///// same between both /////

struct snakepart{
	int     x;
    int     y;
	snakepart(int col,int row);
	snakepart();
};
/////////////////////////////

class snakeclass {

public:

    int             score;
    int             delay;
    bool            eat;
    char            direction;
    int             screenWidth;
    int             screenHeight;

    SDL_Rect        food;
    std::vector<snakepart> snake;

    int             posX;
    int             posY;

    SDL_Window*     window;
    SDL_Renderer*   renderer;
    SDL_Rect        playerCube;
    

    bool            InitEverything();
    bool            InitSDL();
    bool            CreateWindow();
    bool            CreateRenderer();
    void            SetupRenderer();
    void            Render();

    void            putfood();
	bool            collision();
	void            movesnake();



    snakeclass();
    snakeclass(int x, int y);
	~snakeclass();

    void RunGame();

};

#endif