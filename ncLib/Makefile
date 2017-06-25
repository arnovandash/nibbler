CLANG =	clang++

NAME = ncLib.so

CFLAGS = -Wall -Werror -Wextra

C++_TYPE = -std=c++11

NCURSES = -lncurses

HEADER = ncLib.hpp

SRC_PATH = ../src/

SRC = $(SRC_PATH)libs.cpp ncLib.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(C++_TYPE) $(CFLAGS) -fpic $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(NCURSES) -shared -Qunused-arguments -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
