CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -g
CXXXFLAGS = -Wall -Werror -Wextra -lncurses -g
NAME = nibbler 

SRC = src/main.cpp src/Window.cpp src/snake.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXXFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
