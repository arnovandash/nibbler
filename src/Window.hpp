

#ifndef WINDOW_HPP
# define WINDOW_HPP

#define WINHEIGHT 30
#define WINWIDTH 100
#define SHIPX 5
#define SHIPY 5


#include <ncurses.h>
#include <sys/time.h>

class Window {

public:

	Window(int height, int width);
	Window(Window const &);
	~Window();

	Window const &	operator=(Window const &);
	
	void	createWin();
	void	destroyWin();
	void	pewPew();

private:
	unsigned long	timeFrameCount;
	struct timeval	start;
	struct timeval	now;
	WINDOW			*newScr;
	const int		HEIGHT;
	const int		WIDTH;
	const int		WSTARTX;
	const int		WSTARTY;

	void	init();

	unsigned int 	timediff(timeval t1, timeval t2);
};

#endif

