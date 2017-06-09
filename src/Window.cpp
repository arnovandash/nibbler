

#include "Window.hpp"
#include <ncurses.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>


Window::Window(int height, int width) : HEIGHT(height), WIDTH(width), WSTARTX(SHIPX), WSTARTY(SHIPY) {
	init();
}

Window::Window(Window const & src): HEIGHT(WINHEIGHT), WIDTH(WINWIDTH), WSTARTX(SHIPX), WSTARTY(SHIPY) {

	init();
	*this = src;
}

Window::~Window() {
	destroyWin();
    endwin();
	std::cout << "Game Over.... pew pew" << std::endl;
}

Window const &	Window::operator=(Window const & rhs) {
	if (this != &rhs) {
		this->start = rhs.start;
		this->now = rhs.now;
	}
	return *this;
}

void	Window::createWin() {

    newScr = newwin(HEIGHT, WIDTH, WSTARTY, WSTARTX);
    box(newScr, 0 , 0);
    wrefresh(newScr);
}

void	Window::destroyWin() {
    wrefresh(newScr);
    clear();
    refresh();
    delwin(newScr);
}

void	Window::init() {

	initscr();

	
	noecho();
	curs_set(false);
	timeout(0);
	cbreak();
	keypad(stdscr, true);

	gettimeofday(&start, NULL);
	refresh();
	createWin();
	sleep(3);

}

	unsigned int    Window::timediff(timeval t1, timeval t2) {

		return ((t2.tv_sec * 1000000 + t2.tv_usec) - (t1.tv_sec * 1000000 + t1.tv_usec));
	}
