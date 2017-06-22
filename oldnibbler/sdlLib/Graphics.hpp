#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

# include <SDL.h> //check
# include "../src/IGraphics.hpp"

class Graphics : public IGraphics {
public:
	Graphics(const Snake &);
	~Graphics(void);

	void				update(void);

private:
	const Snake &		_snake;
	int _posX = 0;
	int _posY = 0;
	//int _sizeX = 640;
	//int _sizeY = 480;

	SDL_Window * 		_window;
};

extern "C" IGraphics *	graphicsLib_instantiate(const Snake &);
extern "C" void			graphicsLib_uninstantiate(IGraphics * g);


#endif