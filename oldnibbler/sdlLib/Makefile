NAME        =    sdlLib.so
SRC         =    Graphics.cpp
OBJ         =    $(SRC:.cpp=.o)

CPP         ?=    	clang++
CPPFLAGS    ?=    	-Wall -Wextra -Werror -std=c++11
CPPFLAGS 	+=		-g $(shell sdl2-config --cflags)	
LDFLAGS     =    	-shared -fPIC
LDFLAGS		+= 		$(shell sdl2-config --libs)

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(LDFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
