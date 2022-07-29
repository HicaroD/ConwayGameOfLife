CC=gcc
OBJ_NAME=life
CCFLAGS=-Wextra -Wall -Werror
LDFLAGS=/usr/include/SDL2 -D_REENTRANT -pthread -lSDL2

game: main.c
	$(CC) $(CCFLAGS) main.c -o $(OBJ_NAME) -I$(LDFLAGS)
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
