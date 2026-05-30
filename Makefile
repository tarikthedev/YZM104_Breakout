CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lmingw32 -lSDL2main -lSDL2

all:
	$(CC) main.c -o breakout $(CFLAGS) $(LDFLAGS)

clean:
	rm -f breakout.exe