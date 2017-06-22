#include <fstream>
#include <limits.h>
#include <cstdlib>
#include <iostream>
#include "Map.hpp"

Map::Map() : width(_width), height(_height), spawn(_spawn) {
}

Map::Map(unsigned w, unsigned h) : _width(w), _height(h), width(_width), height(_height), spawn(_spawn) {
	map = new unsigned*[height];

	for (unsigned y = 0; y < height; y++) {
		map[y] = new unsigned[width];

		for (unsigned x = 0; x < width; x++) {
			if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
				map[y][x] = BLOCK_WALL;
			else
				map[y][x] = BLOCK_NONE;
		}
	}

	_spawn.first = width / 2;
	_spawn.second = height / 2;
}

Map::~Map(void) {
	unsigned	i;

	i = 0;
	while (i < _height) {
		delete map[i];
		i++;
	}
	delete map;
}

unsigned	Map::getBlock(t_block block) const {
	if (block.first >= width || block.second >= height)
		return (BLOCK_OUT);

	return map[block.second][block.first];
}

void		Map::setBlock(const t_block block, unsigned value) {
	if (getBlock(block) == BLOCK_OUT)
		return ;

	map[block.second][block.first] = value;
}

void	Map::setWidth(unsigned width) {
	_width = width;
}

void	Map::setHeight(unsigned height) {
	_height = height;
}

const char *	Map::BadMapException::what() const throw() {
	return "Bad input map.";
}
