
all: snake

snake: snake.c
	gcc snake.c -o snake -Wall -lncurses
