CC=/usr/bin/gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g -framework OpenGL -framework GLUT -Wno-deprecated-declarations -fsanitize=address 

cells: world.c cells.c
	$(CC) $(CFLAGS) -o cells world.c

cells8: world8.c cells8.c
	$(CC) $(CFLAGS) -o cells8 world8.c