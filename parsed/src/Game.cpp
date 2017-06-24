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
    steps = 0;
    direction = 'l';
    current_lib = 0;
    pause = false;
    lib_closed = true;
    map = nullptr;
    GLibHandler = NULL;
    gameRun = false;

    std::cout << "Game constructor called" << std::endl;
}

Game::Game(unsigned int width, unsigned int height) {
    screenWidth = width;
    screenHeight = height;
    std::cout << "Game x y constructor called" << std::endl;
}

Game::Game(Game const &src) {
    *this = src;
}

Game::~Game() {
    /*
    delete food;

    if (map != nullptr) {
        for (unsigned int y = 0; y < screenHeight + 2; y++) {
            if (map[y] != NULL)
                delete map[y];
        }
        delete[ ] map;
    }
    delete snake;
    if (snake.size() > 0) {
        for (unsigned int i = 0; count < snake.size(); i++) {
            delete this->snake[i];
        }
    }
    */
    std::cout << "Game destructor called" << std::endl;
}

Game &Game::operator=(Game const &src) {
    screenWidth = src.screenWidth;
    screenHeight = src.screenHeight;
    steps = src.steps;
    direction = src.direction;
    current_lib = src.current_lib;
    pause = src.pause;
    score = src.score;

    return (*this);
}

bool Game::collision()
{
	if (snake[0].x == 0 || snake[0].x == screenWidth - 1 || snake[0].y == 0 || snake[0].y == screenHeight - 1)
		gameRun = false;
	
	for (unsigned long i = 2; i < snake.size(); i++) {
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			gameRun = false;
	}

	if (snake[0].x == food.x && snake[0].y == food.y) {
		eat = true;
		putfood();
		score += 10;

		// if((score % 100) == 0)
		// 	delay -= 10000;
	}
	else
		eat = false;
    
    if  (!eat) {
		// Render();
		snake.pop_back();
	}
	
	if (direction == 'l')
		snake.insert(snake.begin(), Part(snake[0].x - 1, snake[0].y));
	else if (direction == 'r')
		snake.insert(snake.begin(),Part(snake[0].x + 1,snake[0].y));
	else if (direction == 'u')
		snake.insert(snake.begin(),Part(snake[0].x,snake[0].y - 1));
	else if (direction == 'd')
		snake.insert(snake.begin(),Part(snake[0].x, snake[0].y + 1));
	
    return false;
}

void Game::putfood()
{
	while(1) {
		unsigned int tmpx = rand() % screenWidth + 1;
		unsigned int tmpy = rand() % screenHeight + 1;

		for(unsigned long i = 0; i < snake.size(); i++)
			if(snake[i].x == tmpx && snake[i].y == tmpy)
				continue;
		if(tmpx >= screenWidth - 2 || tmpy >= screenHeight - 3)
			continue;
		food.x = tmpx;
		food.y = tmpy;
		break;
	}
}

void Game::mapSymbols() {
    // int tmp_x = 0;
    // int tmp_y = 0;

    if (food.x != 0 && food.y != 0)
        map[food.y][food.x] = '*';

    for (unsigned int i = 0; i < snake.size(); i++) {
        map[snake[i].x][snake[i].y] = 'O';
    }
}

void Game::LoadMap() {
    map = new char * [screenHeight + 2];

    if (map == nullptr)
        throw ("Memory Not Allocated: Bad Alloc.");
	for (unsigned int y = 0; y < (screenHeight + 2); y++) {
		map[y] = new char[screenWidth + 2];
        if (map[y] != nullptr) {
            for (unsigned int x = 0; x < screenWidth + 2; x++) {
                map[y][x] = ' ';
            }
        }
        else
            throw ("Memory Not Allocated: Bad Alloc.");
	}

    for (unsigned int y = 0; y < (screenHeight + 2); y++) {
        for (unsigned int x = 0; x < screenWidth + 2; x++) {
            if (y == 0)
                map[y][x] = '/';
            else if (y == (screenHeight + 2) - 1)
                map[y][x] = '/';
        }
        map[y][0] = '/';
        map[y][(screenWidth + 2) - 1] = '/';
	}
    mapSymbols();
}

void Game::create_snake() {
    for(int i = 0; i < 5; i++)
		snake.push_back(Part((screenWidth / 2), ((screenHeight / 2) + i)));

}

void Game::initialise(unsigned int width, unsigned int height)
{
    // this->froot = new food(0, 0, false);
    screenHeight = height;
    screenWidth = width;
    food.x = 0;
    food.y = 0;
    // if (this->froot == nullptr || this->s_froot == nullptr)
    //     throw ("Memory Not Allocated: Bad Alloc.");
    direction = 'l';
    current_lib = 5;
    //user_input(argc, argv);
    load_lib(PATH_NCURSES);
    create_snake();
    LoadMap();
}

void Game::movesnake()
{
    // int tmp_dir = snake[0]->GetPartDir();
    char tmp_dir = direction;
    int tmp_x = snake[0].x;
    int tmp_y = snake[0].y;
    int ret_tmp = 0;

    ret_tmp = lib->Input(direction, current_lib);

    if (ret_tmp > 4)
        change_lib(ret_tmp);
    else if (pause == false)
    {
        direction = ret_tmp;

        switch (direction)
        {
            case 1: // UP
                snake[0].y = tmp_y - 1;
                break ;
            case 2: // RIGHT
                this->snake[0].x = tmp_x + 1;
                break ;
            case 3: // DOWN
                this->snake[0].y = tmp_y + 1;
                break ;
            case 4: // LEFT
                this->snake[0].x = tmp_x - 1;
                break ;
        }

        int tmpx = 0;
        int tmpy = 0;
        int tmpdir = 0;

        if (direction != tmp_dir)
            direction = tmp_dir;

        for (unsigned int i = 1; i < this->snake.size(); i++)
        {
            tmpx = snake[i].x;
            tmpy = snake[i].y;
            tmpdir = direction;

            snake[i].y = tmp_y;
            snake[i].x = tmp_x;
            direction = tmp_dir;

            tmp_x = tmpx;
            tmp_y = tmpy;
            tmp_dir = tmpdir;
        }

        map[tmp_y][tmp_x] = ' ';
        collision();
    }
}

void Game::change_lib(int &ret_tmp) {
    if (ret_tmp == 9) {
        pause = !pause;
        return ;
    }
    else
        this->current_lib = ret_tmp;

    close_lib();
    switch (current_lib)
    {
        case 5:
            load_lib(PATH_NCURSES);
            break ;
        case 6:
            load_lib(PATH_SDL);
            break ;
        case 7:
            break ;
        case 8:
            gameRun = false;
            break ;
    }

    pause = true;
}

void Game::RunGame() {
    gameRun = true;

	srand(time(0));
	while (gameRun) {
    	movesnake();
        if (pause == false) {
            // if (rand() % 100 == 9 && this->s_froot->GetIsFood() == false)
            //     spawn_special_froot();
            if (eat == true)
                putfood();
            mapSymbols();
            steps += 1;
        }
        if (gameRun == true)
            lib->Render(map, score, pause);
    	usleep(70000);
	}

    if(!lib_closed)
        close_lib();
}

void Game::load_lib(std::string const &lib_path) {
    GLibHandler = dlopen(lib_path.c_str(), RTLD_LAZY);

    if (GLibHandler == NULL)
        throw ("Load Error: \"Dynamic library cannot be opened\"");

    // load the symbols
    create_t* create_lib = (create_t *) dlsym(GLibHandler, "create");

    const char* dlsym_error = dlerror();
    if (dlsym_error)
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