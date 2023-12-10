SRC = $(wildcard *.cpp) $(wildcard */*.cpp)

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++1z -stdlib=libc++ \
 -W -Wall -Wextra -Werror \
 -I/opt/homebrew/Cellar/boost/1.83.0/include

NAME = corepp

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@./$(NAME)

.PHONY: clean fclean test
