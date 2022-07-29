CC=gcc
OBJ_NAME=life

game: main.c
	$(CC) main.c -o $(OBJ_NAME)
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
