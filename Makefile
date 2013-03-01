CC=g++

CFLAGS=-Wall -Wextra -g -O2

main:
	$(CC) $(CFLAGS) src/util.cpp src/ciphertext.cpp src/main.cpp -o kry

clean:
	rm -f kry

