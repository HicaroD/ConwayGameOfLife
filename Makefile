CC=gcc
OBJ_NAME=life
CCFLAGS=-Wextra -Wall -Werror
LDFLAGS=/usr/include/SDL2 -D_REENTRANT -pthread -lSDL2
SOURCE_FILES=main.c game.c

game: main.c game.c game.h
	$(CC) $(CCFLAGS) $(SOURCE_FILES) -o $(OBJ_NAME) -I$(LDFLAGS)
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
