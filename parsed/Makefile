CLANG =	clang++

NAME = Nibbler

CFLAGS = -Wall -Werror -Wextra

C++_TYPE = -std=c++11

HEADER = ./inc/

SRC_PATH = ./Src/

SRC = $(SRC_PATH)main.cpp $(SRC_PATH)Game.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(CFLAGS) $(C++_TYPE) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C ./ncurses/

	$(CLANG) $(CFLAGS) $(C++_TYPE) -Qunused-arguments -o $(NAME) $(OBJ) -ldl

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
	make -C ./ncurses/ re


libs:
	make -C ./ncurses/


lib_clean:
	make -C ./ncurses/ fclean


c_e: fclean lib_clean
