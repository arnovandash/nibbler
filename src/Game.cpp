#include "../inc/Game.hpp"


Part::Part(unsigned int col, unsigned int row) {
	x = col;
	y = row;
}

Part::Part() {
	x = 0;
	y = 0;
}

Game::Game() {
	screenWidth = 0;
	screenHeight = 0;
	current_lib = 0;
	lib_closed = true;
	GLibHandler = NULL;
	gameRun = false;

	std::cout << "Game constructor called" << std::endl;
}

Game::Game(unsigned int width, unsigned int height) {
	screenWidth = width;
	screenHeight = height;
	std::cout << "Bummer dude, your Gunther rank is: " << score << std::endl;
}

Game::Game(Game const &src) {
	*this = src;
}

Game::~Game() {
	std::cout << "Game destructor called" << std::endl;
}

Game &Game::operator=(Game const &src) {
	screenWidth = src.screenWidth;
	screenHeight = src.screenHeight;
	current_lib = src.current_lib;

	return (*this);
}
void Game::initialise()
{
	food.x=0;
	food.y=0;
	for(int i=0;i<5;i++)
		snake.push_back(Part(i + screenWidth / 2,screenHeight / 2));
	gameRun = true;
	pause = false;
	keyPress = 0;
	score = 0;
	delay = 110000;
	eat = false;

	direction = 'l';
	srand(time(NULL));
	putfood();
	// Default starting library
	load_lib("ncLib/ncLib.so");
	//	load_lib("sdlLib/sdlLib.so");
	//	load_lib("partyLib/sdlLib.so");
}

void Game::runGame() {
	while (gameRun) {
		if (!pause) {
			if (collision()) {
				gameRun = false;
			}
			movesnake();
		}
		usleep(delay);
		keyPress = lib->Render(food.x, food.y, snake);
		parseKey(keyPress);
	}
	if(!lib_closed && !gameRun)
		close_lib();
}


void Game::putfood()
{
	while(1) {
		unsigned int tmpx = (rand() % screenWidth -3);
		unsigned int tmpy = (rand() % screenHeight -3);

		for(unsigned int i = 0; i < snake.size(); i++)
			if(snake[i].x == tmpx && snake[i].y == tmpy)
				continue;
		if(tmpx >= screenWidth - 2 || tmpy >= screenHeight - 3)
			continue;
		food.x = tmpx + 1;
		food.y = tmpy + 1;
		break;
	}
}

void Game::movesnake() {
	if(!eat) {
		snake.pop_back();
	}
	if(direction=='l') {
		snake.insert(snake.begin(),Part(snake[0].x-1,snake[0].y));
	}
	else if(direction=='r'){
		snake.insert(snake.begin(),Part(snake[0].x+1,snake[0].y));
	}
	else if(direction=='u'){
		snake.insert(snake.begin(),Part(snake[0].x,snake[0].y-1));
	}
	else if(direction=='d'){
		snake.insert(snake.begin(),Part(snake[0].x,snake[0].y+1));
	}
}

void Game::parseKey(int key) {
	switch (key)
	{
		case 1:
			if (direction != 'd')
				direction = 'u';
			break;
		case 2:
			if (direction != 'u')
				direction = 'd';
			break;
		case 3:
			if (direction != 'r')
				direction = 'l';
			break;
		case 4:
			if (direction != 'l')
				direction = 'r';
			break;
		case 5:
			pause = true;
			close_lib();
			load_lib("ncLib/ncLib.so");
			break;
		case 6:
			pause = true;
			close_lib();
			load_lib("sdlLib/sdlLib.so");
			break;
		case 7:
			pause = true;
			close_lib();
			load_lib("partyLib/sdlLib.so");
			break;
		case 8:
			gameRun = false;
			break;
		case 9:
			pause ? pause = false : pause = true;
			break;
	}
}

void Game::load_lib(std::string const &lib_path) {
	GLibHandler = dlopen(lib_path.c_str(), RTLD_LAZY);

	if (GLibHandler == NULL)
		throw ("Load Error: \"Dynamic library cannot be opened\"");

	// load the symbols
	create_t* create_lib = (create_t *) dlsym(GLibHandler, "create");

	const char* dlsym_error = dlerror();
	if (dlsym_error
	   )
		throw (dlsym_error);

	// create an instance of the class
	lib = create_lib();

	if (lib->Init(screenWidth, screenHeight))
		throw ("library initialization Error: \"failed.\"");

	this->lib_closed = false;

}

void Game::close_lib() {
	destroy_t* destroy_lib = (destroy_t*) dlsym(GLibHandler, "destroy");

	const char* dlsym_error = dlerror();
	if (dlsym_error)
		throw (dlsym_error);

	destroy_lib(lib);

	// unload the library
	dlclose(GLibHandler);

	lib_closed = true;
}

bool Game::collision()
{
	if(snake[0].x == 0 || snake[0].x == screenWidth - 1 || snake[0].y == 0 || snake[0].y == screenHeight - 2)
		return true;

	for(unsigned long i = 2; i < snake.size(); i++) {
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return true;
	}
	if(snake[0].x==food.x && snake[0].y==food.y) {
		eat = true;
		putfood();
		score+=10;
		if((score % 30) == 0)
			delay -= 10000;
	}
	else
		eat = false;
	return false;
}

















