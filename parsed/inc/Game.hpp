#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <dlfcn.h>
#include <curses.h>
#include <stdlib.h>
#include <term.h>
//#include "Snek.hpp"
#include "libs.hpp"
//#include "food.hpp"

#define DEFAULT_WIN_X 60
#define DEFAULT_WIN_Y 30
#define PATH_SDL "./sdl/sdl.so"
#define PATH_NCURSES "./ncurses/ncurses.so"

struct Part{
	unsigned int     x;
    unsigned int     y;
	Part(unsigned int col, unsigned int row);
	Part();
};

class Game
{
    private:
        
        dynamic_libs *      lib;

        unsigned int        score;
        //int                 delay;
        bool                eat;
        char                direction;
        unsigned int        screenWidth;
        unsigned int        screenHeight;

        void *              GLibHandler;
        bool                gameRun;
        char **             map;
        int                 steps;
        int                 current_lib;
        bool                pause;
        bool                lib_closed;

        Part 	            food;
	    std::vector<Part>   snake;

    public:
        Game(void);
        Game(unsigned int width, unsigned int height);
        Game(Game const &src);
        ~Game(void);

        Game &operator=(Game const &obj);

        void 		        putfood();
	    bool 		        collision();
	    void 	        	movesnake();
        void                RunGame();

        // void user_input(int argc, char **argv);
         void               initialise(unsigned int width, unsigned int height);
        // void game_loop();
        // int check_digit(char *str);
         void               LoadMap();
         void               mapSymbols();
        // void add_placeholders();
         void               create_snake();
        // void move_snek();
        //void    move_snake();
         void               change_lib(int &ret_tmp);
        // void check_colision();
        // void spawn_froot();
        // void spawn_special_froot();
         void               load_lib(std::string const &lib_path);
         void               close_lib();
};
