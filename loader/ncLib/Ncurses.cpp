#include "Ncurses.hpp"

extern "C" dynamic_libs *create() {
	return (new ncurses);
}

extern "C" void destroy(dynamic_libs *obj) {
	delete obj;
}

ncurses::ncurses() {
	max_width = 0;
	max_height = 0;
	stdscr_x = 0;
	stdscr_y = 0;
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

bool	ncurses::Init() {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	return (false);
}

void ncurses::Render()
{
	mvprintw(1,1,"sssssssssssssssss");
	std::cout << "test" << std::endl;
}

int ncurses::Input(int &lib)
{
	int tmp = getch();
	std::cout << tmp << std::endl;
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
	return (0);
}

