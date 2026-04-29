NAME=ex03
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Iinclude -I../ex02/include
SRCS=src/main.cpp src/Point.cpp src/bsp.cpp

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
