CXX ?= g++

SRC = $(wildcard *.cpp) $(wildcard */*.cpp)

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++20 -W -Wall -Wextra -Werror

NAME = corepp

all: $(NAME)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(NAME): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@./$(NAME)

.PHONY: clean fclean test
