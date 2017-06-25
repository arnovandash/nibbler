CLANG =	clang++

NAME = sdlLib.so

CFLAGS = -Wall -Werror -Wextra

C++_TYPE = -std=c++11

SDL_lIBS = $(shell sdl2-config --libs)

SDL_CFLAGS = $(shell sdl2-config --cflags)

HEADER = sdlLib.hpp

SRC_PATH = ../src/

SRC = $(SRC_PATH)libs.cpp sdlLib.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(C++_TYPE) $(CFLAGS) $(SDL_CFLAGS) -fpic $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(SDL_lIBS) -shared -Qunused-arguments -o $(NAME) $(OBJ)

sdl2:
	brew install SDL2

sdl2_ttf:
	brew install SDL2_ttf

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
