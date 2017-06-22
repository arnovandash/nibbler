NAME		=	ncursesLib.so
SRC			=	$(shell ls | grep ".cpp")
OBJ			=	$(subst .cpp,.o,$(SRC))

CPP			?=	clang++
CPPFLAGS	?=	-Wall -Wextra -Werror -std=c++11
LDFLAGS		=	-shared -fPIC -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(LDFLAGS) -o $(NAME) $(OBJ)

re: fclean all

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
