CC=g++
OBJ_NAME=life
CCFLAGS=-Wextra -Wall -Werror
LDFLAGS=/usr/include/SDL2 -D_REENTRANT -pthread -lSDL2
SOURCE_FILES=main.cpp game.cpp

game: main.cpp game.cpp game.hpp
	$(CC) $(CCFLAGS) $(SOURCE_FILES) -o $(OBJ_NAME) -I$(LDFLAGS)
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
