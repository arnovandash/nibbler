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
    // max_width = obj.GetX();
    // max_height = obj.GetY();
	max_height = src.max_height;
	max_width = src.max_width;

    return (*this);
}

bool	ncurses::Init(unsigned int &maxX,unsigned int &maxY) {
	
	initscr();
    getmaxyx(stdscr, max_y, max_x);

    if (stdscr_y < 40 || stdscr_x < 40)
        mvprintw(stdscr_y / 2, (stdscr_x / 2) - 15,"Please enlarge terminal window: Too small");

    max_height = maxY;
    max_width = maxX;

	raw();
	noecho();
    nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
    curs_set(FALSE);

    return (false);

	// partchar = 'x';
	// wall=(char)219;
	// lunch='*';
	// food.x = 0;
	// food.y = 0;

	// for(int i=0;i<5;i++)
	// 	snake.push_back(snakepart(40+i,10));

	// score=0;
	// delay=110000;
	// eat=0;
	// direction='l';
	//srand(time(NULL));
	// putfood();

	// for(int i=0;i<screenWidth-1;i++) {
	// 	move(0,i);
	// 	addch(wall);
	// }

	// for(int i=0;i<screenHeight-1;i++) {
	// 	move(i,0);
	// 	addch(wall);
	// }

	// for(int i=0;i<screenWidth-1;i++) {
	// 	move(screenHeight-2,i);
	// 	addch(wall);
	// }

	// for(int i=0;i<screenHeight-1;i++) {
	// 	move(i,screenWidth-2);
	// 	addch(wall);
	// }

	// for(unsigned long i=0; i<snake.size(); i++) {
	// 	move(snake[i].y,snake[i].x);
	// 	addch(partchar);
	// }
	// move(screenHeight-1,0);
	// printw("%d",score);
	// move(food.y,food.x);
	// addch(lunch);
	// refresh();
}

void ncurses::Render(char **map, unsigned int &score, bool &pause)
{
    clear();

    getmaxyx(stdscr, stdscr_y, stdscr_x);
    if (stdscr_y < 40 || stdscr_x < 40)
    {
        mvprintw(stdscr_y / 2, (stdscr_x / 2) - 15,"Please enlarge terminal window: Too Small");
        pause = true;
        return ;
    }

    for (int y = 0; y < (max_height + 2); y++)
    {
        for (int x = 0; x < max_width + 2; x++)
        {
            printw("%c", map[y][x]);
        }
        printw("\n");
    }
    mvprintw(max_height + 3, 0, "Score: %d", score);
    refresh();
}

// snakeclass::~snakeclass() {
// 	nodelay(stdscr,false);
// 	getch();                                                                                //wait until a key is pressed
// 	endwin();
// }

// void snakeclass::putfood()
// {
// 	while(1) {
// 		int tmpx = rand() % screenWidth + 1;
// 		int tmpy = rand() % screenHeight + 1;

// 		for(unsigned long i = 0; i < snake.size(); i++)
// 			if(snake[i].x == tmpx && snake[i].y == tmpy)
// 				continue;
// 		if(tmpx >= screenWidth - 2 || tmpy >= screenHeight - 3)
// 			continue;
// 		food.x = tmpx;
// 		food.y = tmpy;
// 		break;
// 	}
// 	move(food.y, food.x);
// 	addch(lunch);
// 	refresh();
// }

// bool snakeclass::collision()
// {
// 	if(snake[0].x == 0 || snake[0].x == screenWidth - 1 || snake[0].y == 0 || snake[0].y == screenHeight - 2)
// 		return true;
	
// 	for(unsigned long i = 2; i < snake.size(); i++) {
// 		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
// 			return true;
// 	}

// 	if(snake[0].x==food.x && snake[0].y==food.y) {
// 		eat = true;
// 		putfood();
// 		score+=10;

// 		move(screenHeight-1,0);
// 		printw("%d",score);

// 		if((score % 100) == 0)
// 			delay -= 10000;
// 	}
// 	else
// 		eat = false;
// 	return false;
// }

char ncurses::input(char &direction, char &lib)
{
	int tmp = getch();
	switch(tmp)
	{
		case KEY_LEFT:
			if(direction != 'r'){
				direction = 'l';
				return direction;
			}
			break;
		case KEY_UP:
			if(direction != 'd') {
				direction = 'u';
				return direction;
			}
			break;
		case KEY_DOWN:
			if(direction != 'u') {
				direction = 'd';
				return direction;
			}
			break;
		case KEY_RIGHT:
			if(direction != 'l') {
				direction = 'r';
				return direction;
			}
			break;

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
    return (dir);
}
// void snakeclass::movesnake() {

// 	int tmp=getch();
// 	switch(tmp)
// 	{
// 		case KEY_LEFT:
// 			if(direction!='r')
// 				direction='l';
// 			break;
// 		case KEY_UP:
// 			if(direction!='d')
// 				direction='u';
// 			break;
// 		case KEY_DOWN:
// 			if(direction!='u')
// 				direction='d';
// 			break;
// 		case KEY_RIGHT:
// 			if(direction!='l')
// 				direction='r';
// 			break;
// 		case KEY_BACKSPACE:
// 			direction='q';
// 			break;
// 	}

// 	if(!eat) {
// 		move(snake[snake.size()-1].y,snake[snake.size()-1].x);
// 		printw(" ");
// 		refresh();
// 		snake.pop_back();
// 	}
// 	if(direction=='l') {
// 		snake.insert(snake.begin(),snakepart(snake[0].x-1,snake[0].y));
// 	}
// 	else if(direction=='r'){
// 		snake.insert(snake.begin(),snakepart(snake[0].x+1,snake[0].y));

// 	}
// 	else if(direction=='u'){
// 		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y-1));
// 	}
// 	else if(direction=='d'){
// 		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y+1));
// 	}
// 	move(snake[0].y,snake[0].x);
// 	addch(partchar);
// 	refresh();
// }

// void snakeclass::RunGame() {
// 	while(1) {
// 		if(collision()) {
// 			move(12,36);
// 			printw("game_over");
// 			break;
// 		}
// 		movesnake();
// 		if(direction=='q')
// 			break;
// 		usleep(delay);
// 	}
// }
