CXX  = /usr/local/opt/llvm/bin/clang++

SRC = $(wildcard *.cpp) $(wildcard */*.cpp)

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++1z -stdlib=libc++ \
 -W -Wall -Werror

NAME = corepp

all: $(NAME)

LIBS = -I/usr/local/Cellar/boost/1.57.0/include

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LIBS) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@./$(NAME)

.PHONY: clean fclean test
