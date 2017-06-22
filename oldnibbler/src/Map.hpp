#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <exception>

# define BLOCK_OUT		0
# define BLOCK_NONE		1
# define BLOCK_WALL		2
# define BLOCK_SPAWN	3
# define BLOCK_FOOD		4
# define BLOCK_HEAD		10

typedef std::pair<unsigned, unsigned>	t_block;

class Map
{
protected:
	unsigned			_width;
	unsigned			_height;
	t_block				_spawn;

public:
	class BadMapException : std::exception
	{
	public:
		virtual const char *	what() const throw();
	};

	const unsigned &	width;
	const unsigned &	height;
	const t_block &		spawn;
	unsigned **			map;

	Map(unsigned, unsigned);
	Map(void);
	~Map(void);

	void				setWidth(unsigned);
	void				setHeight(unsigned);
	void				setBlock(t_block, unsigned);
	unsigned			getBlock(t_block) const;
};

#endif
