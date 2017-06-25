CLANG =	g++

NAME = Nibbler

CFLAGS = -Wall -Werror -Wextra -g

C++_TYPE = -std=c++11

HEADER = ./inc/

SRC_PATH = ./src/

SRC = $(SRC_PATH)main.cpp $(SRC_PATH)libs.cpp $(SRC_PATH)Game.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(CFLAGS) $(C++_TYPE) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C ./ncLib/
	make -C ./sdlLib/
	make -C ./partyLib/

	$(CLANG) $(CFLAGS) $(C++_TYPE) -o $(NAME) $(OBJ) -ldl

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
	make -C ./ncLib/ re
	make -C ./sdlLib/ re
	make -C ./partyLib/ re


libs:
	make -C ./ncLib/
	make -C ./sdlLib/
	make -C ./partyLib/


lib_clean:
	make -C ./ncuLib/ fclean
	make -C ./sdlLib/ fclean
	make -C ./partyLib/ fclean

c_e: fclean lib_clean
