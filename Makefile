all: server-3x3.x server-9x9.x random.x

CPPFLAGS=-Wall -Wextra -pedantic --std=c++11 -O3
CFLAGS=-Wall -Wextra -pedantic -Wno-unused-result -Wno-unused-parameter -D_POSIX_SOURCE -ansi -O3

server-3x3.x: server-3x3.c
	gcc $(CFLAGS) -o server-3x3.x server-3x3.c

server-9x9.x: server-9x9.c
	gcc $(CFLAGS) -o server-9x9.x server-9x9.c

random.x: random.cpp
	g++ $(CPPFLAGS) -o random.x random.cpp

clean:
	rm -f random.x server-3x3.x server-9x9.x


