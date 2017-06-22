#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <string>
# include "Map.hpp"
# include "Player.hpp"

# define DEFAULT_SPEED	1.0f
# define SPEED_INC		30.0f
# define MAX_SPEED		0.10f
# define MULTIFOOD_RATE	10

class LibSelector;

typedef enum		e_input {
	NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	PAUSE,
	QUIT,
	LIB1,
	LIB2
	//LIB3
}					t_input;

class Snake {
public:

	static Snake *		instance;
	Map *				map;
	Player				player;
	float				speed;
	bool				paused;
	float				clockCountdown;
	bool				stop;
	LibSelector *		libSelector;

	Snake();
	~Snake();
	double				getTime();
	void				loadMap(unsigned, unsigned);
	void				loadMap(void);
	void				loadLibrary(const std::string);
	void				startMap();
	void				gameOver();
	void				spawnFood();
	void				eatFood();
	void				launch();
	void				update();
	void				handleAction();
};

#endif
