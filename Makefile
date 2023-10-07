CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
LFLAGS=-lm

build: main.c
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@

run: build
	./$^

clean:
	rm build
