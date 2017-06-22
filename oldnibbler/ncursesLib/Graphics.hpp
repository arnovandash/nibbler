#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

# include "../src/IGraphics.hpp"

class Graphics : public IGraphics {
public:
	Graphics(const Snake &);
	~Graphics(void);

	void				update(void);

private:
	const Snake &		_snake;
};

extern "C" IGraphics *	graphicsLib_instantiate(const Snake &);
extern "C" void			graphicsLib_uninstantiate(IGraphics * g);


#endif
