CC=g++

CFLAGS= -std=c++0x -Wall -Wextra -g -O2

main:
	$(CC) $(CFLAGS) src/util.cpp src/ngramcounter.cpp src/ciphertext.cpp src/main.cpp -o kry

clean:
	rm -f kry

