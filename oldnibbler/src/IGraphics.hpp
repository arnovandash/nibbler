
#ifndef IGRAPHICS_HPP
# define IGRAPHICS_HPP

# include <queue>
# include "Snake.hpp"

class IGraphics
{
public:
	t_input			graphicsLib_action;

	virtual			~IGraphics(void) = default;
	virtual void	update(void) = 0;
};

#endif

