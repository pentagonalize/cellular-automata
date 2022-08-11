CC=/usr/bin/gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g -framework OpenGL -framework GLUT -Wno-deprecated-declarations -fsanitize=address 

cells8: world8.c cells8.c transfer8.c
	$(CC) $(CFLAGS) -o cells8 world8.c

cells: world.c cells.c
	$(CC) $(CFLAGS) -o cells world.c

breed: simple_breeder.c cells8.c transfer8.c
	$(CC) $(CFLAGS) -o breed simple_breeder.c

testbreed: treetest.c cells8.c transfer8.c
	$(CC) $(CFLAGS) -o testbreed treetest.c