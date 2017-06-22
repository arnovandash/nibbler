

#ifndef LIBSELECTOR_HPP
# define LIBSELECTOR_HPP

# include <string>
# include <exception>
# include "Snake.hpp"
# include "IGraphics.hpp"

typedef IGraphics *	(*t_sym_instantiate)(const Snake &);
typedef void		(*t_sym_uninstantiate)(IGraphics *);

class LibSelector {
protected:
	const Snake &		_snake;
	void *				_handler;
	t_sym_uninstantiate	_uninstantiate;

public:
	class LibraryNotFoundException : public std::exception {
	public:
		virtual const char *	what() const throw();
	};

	class BadLibraryException : public std::exception {
	public:
		virtual const char *	what() const throw();
	};

	LibSelector(const Snake &);
	~LibSelector();

	static IGraphics *	instance;

	void				loadLibrary(std::string);
	void *				loadSymbol(const std::string);
};

#endif
