SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	include
FILE_EXT	=	cpp

NAME		=	nibbler
BIN_NAME	=	$(NAME)
SRC_FILES	=	main.cpp \
				Snake.cpp \
				Map.cpp \
				Player.cpp \
				LibSelector.cpp

export CPP		=	clang++
export CPPFLAGS	=	-Wall -Werror -Wextra -pedantic -g3 -std=c++11 -stdlib=libc++

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.$(FILE_EXT)=.o))

all: _depend $(BIN_NAME)
	@echo "\033[32m•\033[0m $(NAME) is ready."

_depend:
	$(MAKE) -C ncursesLib
	$(MAKE) -C sdlLib

$(BIN_NAME): $(OBJ)
	$(CPP) $(LDFLAGS) -o $(BIN_NAME) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.$(FILE_EXT)
	@mkdir -p $(@D)
	$(CPP) $(CPPFLAGS) -o $@ -c $<

clean:
	$(MAKE) -C ncursesLib clean
	$(MAKE) -C sdlLib clean
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) -C ncursesLib fclean
	$(MAKE) -C sdlLib fclean
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_NAME)

re: fclean all

.PHONY: all re fclean clean $(BIN_NAME)
