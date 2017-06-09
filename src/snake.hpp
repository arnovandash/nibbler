#ifndef SNAKE_HPP
#define SNAKE_HPP

enum Direction {Up=1 , Right, Down, Left};

class snake {
	public:

		snake();
        snake(int a, int b);

		snake(const snake &ekans);
		void setCh(char x);
		char getCh();
		int getX();
		void setX(int no);
		int getY();
		void setY(int no);

    private:
        int x, y;
	    char ch;
};

class node {   
	node* next;
	snake s;

	public:
		snake getSnake() {
			return s;
		}  
		void setSnake(snake ekans) {
			s= ekans;
		}
		void setNext(node *n) {
			next= n;
		}
		node* getNext() {
			return next;
		}
};

class list {
	node* head;
	int length;

	public:
	list() {
		head= NULL;
		length= 0;
	}
	void add(snake s) {
		node *n= new node;
		n->setSnake(s);
		n->setNext(head);
		head= n;
		length++;
	}
	int listLength() {
		return length;
	}
	snake get(int n) {
		node *temp =head;
		int count= 1;
		while(count!= n && temp!= NULL) {
			count++;
			temp= temp->getNext();
		} 
		return temp->getSnake();
	}
	void remove() {
		node *temp= head->getNext();
		node *t2= head;
		while(temp->getNext()!=NULL) {
			temp=temp->getNext();
			t2= t2->getNext();
		}
		t2->setNext(NULL);
		delete temp;
		length--;
	}
	void display() {
		int i= 0;
		node *temp= head;
		while(temp!= NULL) {
			mvaddch(10,10+i,temp->getSnake().getCh());
			refresh();
			temp= temp->getNext();
		}
	}
	~list() {
		while(head!= NULL) {
			node* n= head;
			head= head->getNext();
			delete n;
		}
		length= 0;
	}
};

class game
{   
	int score, max_y, max_x, food_x, food_y;// direction, prev_dir;
	Direction direction, prev_dir;
	list l;

	public:
	game() {
		score= max_y= max_x= food_x= food_y= 0;
		prev_dir= direction= Right;
	}
	void launch();
	void play();
	void map();
	void genFood();
	void setSnake();
	void moveSnake(Direction dir);
	bool checkForCollision();
};
void Ngame();

#endif