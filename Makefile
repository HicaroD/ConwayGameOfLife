CC=gcc

game: main.c
	$(CC) main.c -o life
	./life

clean:
	rm life
