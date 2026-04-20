CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = zombieHorde
SRCS = main.cpp Zombie.cpp zombieHorde.cpp

all: $(NAME)

$(NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRCS)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
