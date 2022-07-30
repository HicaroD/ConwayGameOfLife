CC=gcc
OBJ_NAME=life
CCFLAGS=-Wextra -Wall -Werror
LDFLAGS=/usr/include/SDL2 -D_REENTRANT -pthread -lSDL2
FILES=main.c game.h

game: $(FILES)
	$(CC) $(CCFLAGS) $(FILES) -o $(OBJ_NAME) -I$(LDFLAGS)
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
