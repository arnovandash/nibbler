#include <dlfcn.h>
#include <iostream>
#include "LibSelector.hpp"

IGraphics *		LibSelector::instance = NULL;

LibSelector::LibSelector(const Snake & s) : _snake(s) {

}

LibSelector::~LibSelector() {
	_uninstantiate(instance);
	dlclose(_handler);
}

void			LibSelector::loadLibrary(std::string name) {
	t_sym_instantiate	instantiate;

	_handler = dlopen(name.c_str(), RTLD_NOW);

	if (_handler == NULL) {
		std::cout << dlerror() << std::endl;
		throw LibraryNotFoundException();
	}

	instantiate = reinterpret_cast<t_sym_instantiate>(loadSymbol("graphicsLib_instantiate"));
	_uninstantiate = reinterpret_cast<t_sym_uninstantiate>(loadSymbol("graphicsLib_uninstantiate"));
	instance = instantiate(_snake);
}

void *		LibSelector::loadSymbol(const std::string name) {
	const char *	dlsym_error;
	void *			symbol;

	dlerror();
	symbol = dlsym(_handler, name.c_str());
	dlsym_error = dlerror();

	if (dlsym_error)
		throw BadLibraryException();

	return symbol;
}

const char *	LibSelector::LibraryNotFoundException::what() const throw() {
	return "Library not found.";
}

const char *	LibSelector::BadLibraryException::what() const throw() {
	return "Bad graphic library.";
}
