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
//    map = nullptr;
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
	current_lib = 5;
	load_lib("ncLib/ncurses.so");
}

void Game::change_lib(int &ret_tmp) {
	if (ret_tmp == 9) {
		return ;
	}
	else
		this->current_lib = ret_tmp;

	close_lib();
	switch (current_lib)
	{
		case 5:
			load_lib("ncLib/ncurses.so");
			break ;
		case 6:
//			load_lib(PATH_SDL);
			break ;
		case 7:
			break ;
		case 8:
			gameRun = false;
			break ;
	}

}

void Game::RunGame() {
//	gameRun = true;
//	while (gameRun) {
//		if (gameRun == true)
{
//			std::cout << "hello" << std::endl;
			lib->Render();
}
		usleep(70000);
//	}

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

	if (lib->Init())
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
