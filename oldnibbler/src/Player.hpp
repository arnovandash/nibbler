
#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <vector>
# include "Map.hpp"

# define SNAKE_SIZE	5

typedef enum	e_dir
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
}				t_dir;

class Player
{
protected:
	t_block				_findNextBlock(const t_block) const;
	void				_moveBlock(t_block &, t_dir) const;

public:
	t_block				head;
	t_dir				direction;
	t_dir				tempDirection;
	unsigned			size;
	unsigned			tempFood;
	unsigned			score;

	Player();

	void				changeDirection(t_dir);
	void				spawn();
	bool				move();
	void				eat();
};

#endif
