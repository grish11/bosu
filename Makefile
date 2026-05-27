CC=gcc
CFLAGS=-O -Wall

bosu: bosu.c bosu.h
	$(CC) $(CFLAGS) -o bosu bosu.c -lncursesw

clean:
	rm -f bosu

distclean: clean
