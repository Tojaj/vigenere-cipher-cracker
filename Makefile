CC=g++

CFLAGS=-Wall -Wextra -g -O2

main:
	$(CC) $(CFLAGS) src/main.cpp -o kry

clean:
	rm -f kry

