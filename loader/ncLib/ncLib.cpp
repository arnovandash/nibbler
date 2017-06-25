#include "ncLib.hpp"

extern "C" dynamic_libs *create() {
	return (new ncurses);
}

extern "C" void destroy(dynamic_libs *obj) {
	delete obj;
}

ncurses::ncurses() {
	max_width = 0;
	max_height = 0;
	//	stdscr_x = 0;
	//	stdscr_y = 0;
}

ncurses::ncurses(unsigned int tmp_x, unsigned int tmp_y) {
	max_width = tmp_x;
	max_height = tmp_y;
}

ncurses::ncurses(ncurses const &src) {
	*this = src;
}

ncurses::~ncurses() {
	endwin();
}

ncurses &ncurses::operator=(ncurses const &src)
{
	max_height = src.max_height;
	max_width = src.max_width;

	return (*this);
}

bool	ncurses::Init(int Width, int Height) {
	screenWidth = Width;
	screenHeight = Height;
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	wall=(char)219;
	partchar = 'x';
	lunch = '*';
	return (false);
}

int ncurses::Render(int foodX, int foodY, std::vector<Part> snake)
{
	int key = getch();
	clear();
	for(int i=0;i<screenWidth-1;i++) {
		move(0,i);
		addch(wall);
	}
	for(int i=0;i<screenHeight-1;i++) {
		move(i,0);
		addch(wall);
	}
	for(int i=0;i<screenWidth-1;i++) {
		move(screenHeight-2,i);
		addch(wall);
	}
	for(int i=0;i<screenHeight-1;i++) {
		move(i,screenWidth-2);
		addch(wall);
	}
	for(unsigned long i=0; i<snake.size(); i++) {
		move(snake[i].y,snake[i].x);
		addch(partchar);
	}

	// CHECK TERMINAL SIZE
	//	getmaxyx(stdscr,screenHeight,screenWidth);

	//	move(screenHeight-1,0);
	//	printw("%d",score);
	
	move(foodY,foodX);
	addch(lunch);
	switch(key)
	{
		case KEY_UP:
			return (1);
			break;
		case KEY_DOWN:
			return (2);
			break;
		case KEY_LEFT:
			return (3);	
			break;
		case KEY_RIGHT:
			return (4);
			break;
		case 50:// "2" switch lib
			return (6);
			break;
		case 51:// "3" switch lib
			return (7);
			break;
		case 27: // ESC to quit
			return (8);
			break;
		case 32: // SPACE to pause
			return (9);
			break;
	}
	
	refresh();
	return (0);
}

