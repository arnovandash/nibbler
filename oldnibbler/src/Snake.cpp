#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include "Snake.hpp"
#include "LibSelector.hpp"


Snake *	Snake::instance = NULL;

Snake::Snake(void) : map(NULL), speed(DEFAULT_SPEED), paused(false), clockCountdown(0), stop(false) {
	instance = this;
	srand(time(NULL));
}

Snake::~Snake() {
	if (map != NULL)
		delete map;
	if (libSelector != NULL)
		delete libSelector;
}

double	Snake::getTime() {
	static time_t	beginning;
	struct timeval	tod;
	double			ret;

	gettimeofday(&tod, NULL);
	if (beginning == 0)
		beginning = tod.tv_sec;
	ret = static_cast<double>(tod.tv_sec - beginning);
	ret += static_cast<double>(tod.tv_usec) / 1000000;
	return (ret);
}

//############################## make a new map with inputted height and width #########################//

void	Snake::loadMap(unsigned width, unsigned height) {
	if (map != NULL)
		delete map;

	try
	{
		map = new Map(width, height);
		player.spawn();
	}
	catch (Map::BadMapException & e)
	{
		std::cout << "Error while loading the map: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (std::exception & e)
	{
		std::cout << "An unexpected error has occured." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Snake::loadLibrary(const std::string name) {
	if (libSelector != NULL)
		delete libSelector;

	libSelector = new LibSelector(*this);

	try
	{
		libSelector->loadLibrary(name);
	}
	catch (LibSelector::LibraryNotFoundException & e)
	{
		std::cout << "Library error: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (LibSelector::BadLibraryException & e)
	{
		std::cout << "Library error: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Snake::eatFood() {
	t_block	block;

	for (block.first = 0; block.first < map->width; block.first++) {
		for (block.second = 0; block.second < map->height; block.second++) {
			if (map->getBlock(block) == BLOCK_FOOD)
				map->setBlock(block, BLOCK_FOOD);
		}
	}
}

void	Snake::spawnFood() {
	unsigned	random;
	unsigned	i;
	t_block		block;

	random = rand() % (map->height * map->width);
	i = 0;

	while (1) {
		block = { 0, 0 };
		while (block.second < map->height) {
			block.first = 0;
			while (block.first < map->width) {
				if (map->getBlock(block) == BLOCK_NONE) {
					if (i == random)
						return map->setBlock(block, BLOCK_FOOD);
					i++;
				}
				block.first++;
			}
			block.second++;
		}
	}
}

void	Snake::launch() {
	stop = false;
	while (!stop)
		update();
}

void	Snake::update() {
	static float	lastTime;
	float			currentTime;

	if (lastTime == 0 || paused)
		lastTime = getTime();

	LibSelector::instance->update();
	handleAction();

	if (paused)
		return ;

	if (clockCountdown <= 0) {
		player.direction = player.tempDirection;

		if (player.move() == false)
			return gameOver();

		speed = std::max<float>(speed - speed / SPEED_INC, MAX_SPEED);
		while (clockCountdown <= 0)
			clockCountdown += speed;
			
	}
	currentTime = getTime();
	clockCountdown -= currentTime - lastTime;
	lastTime = currentTime;
}

void	Snake::gameOver() {
	std::cout << "You lost with a score of " << player.score << "." << std::endl;
	stop = true;
}

void	Snake::handleAction() {
	switch (LibSelector::instance->graphicsLib_action)
	{
		case UP:
			paused = false;
			player.changeDirection(NORTH);
			break;
		case DOWN:
			paused = false;
			player.changeDirection(SOUTH);
			break;
		case LEFT:
			paused = false;
			player.changeDirection(WEST);
			break;
		case RIGHT:
			paused = false;
			player.changeDirection(EAST);
			break;
		case PAUSE:
			paused = true;
			break;
		case LIB1:
			paused = true;
			loadLibrary("ncursesLib/ncursesLib.so");
			break;
		//############### not implemented yet ###################//
	
		case LIB2:
			paused = true;
			loadLibrary("sdlLib/sdlLib.so");
			break;
		/*
		case LIB3:
			paused = true;
			loadLibrary("openGLLib/openGLLib.so");
			break;
		*/
		case QUIT:
			stop = true;
		case NONE:
			break;
	}

	LibSelector::instance->graphicsLib_action = NONE;
}