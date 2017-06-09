#include<ncurses.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include "snake.hpp"

snake::snake() : x(0), y(0), ch('O') {

}

snake::snake(int a, int b) : x(a), y(b), ch('O') {

}

snake::snake(const snake &ekans) {
	ch = ekans.ch;
	x = ekans.x;
	y = ekans.y;
}

void snake::setCh(char x) {
	ch = x;
}

char snake::getCh() {
	return ch;
}

int snake::getX() {
	return x;
}

void snake::setX(int no) {
	x = no;
}

int snake::getY() {
	return y;
}

void snake::setY(int no) {
	y = no;
}

void game:: launch() {
	initscr();                      //initialize ncurses
	cbreak();                       //no line buffering
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	noecho();
	refresh();
	attron(A_BOLD);
	mvprintw(LINES/2-2, COLS/2-10, "SNAKES WELCOMES YOU");
	mvprintw(LINES/2, COLS/2-12, "PRESS ENTER TO CONTINUE");
	int ch;
	if((ch= getch())==10) {
		getmaxyx(stdscr, max_y, max_x);
		play();
	}
	else {
		clear();
		mvprintw(LINES/2, COLS/2- 16, "YOU DID NOT EVEN GIVE ME A CHANCE......GOODBYE");
		refresh();
		sleep(2);
	}
	attroff(A_BOLD);
	endwin();
}  

void game:: genFood() {
	srand(time(NULL));
	food_y= random()%(max_y-6)+4;
	food_x= random()%(max_x-4)+2;
}

void game:: map() {
	box(stdscr, 0, 0);
	mvprintw(1,1, "SCORE: ");
	mvprintw(1,8, "%d",score);      
	mvprintw(2,1, "Press q to quit");
	refresh();
}

void game:: setSnake() {
	clear();
	map();
	for(int i= 0; i< 8; i++) {
		snake s((COLS/2)-8+i, LINES/2);
		l.add(s);
		mvprintw(s.getY(),s.getX(),"%c",s.getCh());
	}
	mvprintw(food_y, food_x, "F");
	refresh();
}

void game::play() {
	genFood();
	setSnake();
	mvprintw(8, COLS/2-20, "??????????READY??????????????");
	refresh();
	sleep(1);
	int ch= 0;
	timeout(120);                            //adjust speed of the game
	while((ch=getch())!= 'q') {
		switch(ch) {
			case KEY_UP: direction= Up; 
						 break;
			case KEY_DOWN: direction= Down;
						   break;
			case KEY_RIGHT: direction= Right;
							break;
			case KEY_LEFT: direction= Left;
						   break;
		}
		clear();
		map();
		mvprintw(food_y, food_x,"F");
		if(direction+2== prev_dir || prev_dir+2== direction)
			direction= prev_dir;
		moveSnake(direction);
		refresh();
		if(checkForCollision()) {
			clear();
			mvprintw(max_y/2-2, max_x/2-8, "GAME OVER");
			mvprintw(max_y/2, max_x/2-10, "YOUR SCORE %d",score);
			refresh();
			sleep(2);
			break;
		}
		prev_dir= direction;
	}
}

bool game:: checkForCollision() {
	bool collided= false;
	snake s= l.get(1);
	int head_x= s.getX();
	int head_y= s.getY();
	if(head_x== max_x-1 || head_y== 1 || head_x== 1 || head_y== max_y-1)
		return true;
	else {
		int len= l.listLength();
		for(int i= 4; i< len; i++) {
			s= l.get(i);
			if(head_x== s.getX() && head_y== s.getY()) {
				collided= true;
				break;
			}
		}
		return collided;
	}   
}   

void game:: moveSnake(Direction dir) {
	snake k;
	k= l.get(1);
	int x= k.getX(), y= k.getY();
	if(dir== Up)    y--;
	else if(dir== Left) x--;
	else if(dir== Down) y++;
	else x++;
	snake s(x,y);
	l.add(s);
	if(x==food_x && y==food_y) {
		score++; 
		genFood();
		mvprintw(food_y, food_x, "F");
	}
	else
		l.remove();
	int len= l.listLength();
	for(int i= 1; i<= len; i++) {
		k= l.get(i);
		mvaddch(k.getY(), k.getX(), k.getCh());
		refresh();
	}
}       

void Ngame() {
	game g;
	g.launch();
}
