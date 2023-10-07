CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
LFLAGS=

build: main.c
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@

run: build
	./$^

clean:
	rm build
