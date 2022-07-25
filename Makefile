
LD = arm-none-eabi-g++
all: server first

server: server.c
	gcc -o server server.c

first: first.c
	gcc -o first first.c -lc

clean:
	rm -f *.o server first

runs:
	./server

runc:
	./first