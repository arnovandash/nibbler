#include "Player.hpp"
#include "Snake.hpp"
#include <iostream>
#include <climits>

Player::Player() : score(0) {

}

t_block	Player::_findNextBlock(const t_block block) const {
	t_block		coord;
	unsigned	wantedBlock;
	Map *		map;

	map = Snake::instance->map;
	wantedBlock = map->getBlock(block) + 1;
	coord = block;

	coord.first += 1;
	if (map->getBlock(coord) == wantedBlock)
		return (coord);

	coord.first -= 2;
	if (coord.first == UINT_MAX)
		coord.first = 0;

	if (map->getBlock(coord) == wantedBlock)
		return (coord);

	coord.first = block.first;
	coord.second += 1;
	if (map->getBlock(coord) == wantedBlock)
		return (coord);

	coord.second -= 2;
	if (coord.second == UINT_MAX)
		coord.second = 0;

	if (map->getBlock(coord) == wantedBlock)
		return (coord);

	coord.first = UINT_MAX;

	return (coord);
}

void	Player::_moveBlock(t_block & block, t_dir dir) const {
	switch (dir)
	{
		case NORTH:
			block.second -= 1;
			break;
		case WEST:
			block.first += 1;
			break;
		case SOUTH:
			block.second += 1;
			break;
		case EAST:
			block.first -= 1;
	}
}

void	Player::spawn() {
	unsigned	i;
	Map *		map;
	t_block		block;

	direction = WEST;
	tempDirection = direction;
	size = SNAKE_SIZE;
	tempFood = 0;

	map = Snake::instance->map;

	head.first = map->spawn.first;
	head.second = map->spawn.second;
	block = head;
	direction = static_cast<t_dir>((direction + 2) % 4);

	i = 0;
	while (i < size) {
		if (map->getBlock(block) != BLOCK_NONE)
			throw Map::BadMapException();

		map->setBlock(block, BLOCK_HEAD + i);
		_moveBlock(block, direction);
		i++;
	}
	direction = static_cast<t_dir>((direction + 2) % 4);

	Snake::instance->spawnFood();
}

void	Player::eat() {
	unsigned	random;

	random = rand() % MULTIFOOD_RATE;
	tempFood++;
	size++;
	score++;
	Snake::instance->eatFood();
	Snake::instance->spawnFood();
}

bool	Player::move() {
	t_block		prevBlock;
	t_block		nextBlock;
	unsigned	i;
	Map *		map;

	map = Snake::instance->map;
	nextBlock = head;
	_moveBlock(head, direction);
	prevBlock = head;

	switch (map->getBlock(head))
	{
		case BLOCK_NONE:
			break;
		case BLOCK_FOOD:
			eat();
			break;
		default:
			return false;
	}

	i = BLOCK_HEAD - 1;

	while (map->getBlock(nextBlock) > i) {
		map->setBlock(prevBlock, map->getBlock(nextBlock));
		prevBlock = nextBlock;
		nextBlock = _findNextBlock(prevBlock);
		i++;
	}

	if (tempFood > 0) {
		tempFood--;
		map->setBlock(prevBlock, i + 1);
	}
	else
		map->setBlock(prevBlock, BLOCK_NONE);

	return true;
}

void	Player::changeDirection(t_dir dir) {
	if (direction % 2 != dir % 2)
		tempDirection = dir;
	else
		tempDirection = direction;
}
