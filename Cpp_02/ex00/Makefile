NAME=fixed
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Iinclude
SRCS=src/main.cpp src/Fixed.cpp

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
