CC = gcc -Wall -Werror -Wextra

all: clean
	$(CC) main.c util.c screen.c move.c -o tetris -lncurses -g && ./tetris

style:
	clang-format -n --style=google *.c *.h

clang:
	clang-format -i --style=google *.c *.h

clean:
	rm -rf a.* tetris tetris.d*