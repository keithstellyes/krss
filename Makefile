INC := -I /usr/include/libxml2
CC := gcc -O2 $(INC)

all: rss-console rss-curses

rss.o: rss.c rss.h shared.o
	$(CC) rss.c -c

rss-console: rss-console.o rss.o shared.o
	$(CC) rss.o rss-console.o shared.o -o rss-console -lxml2

rss-console.o: rss.h shared.o
	$(CC) rss-console.c -c

rss-curses: rss-curses.o rss.o
	$(CC) -lncurses -lxml2 rss-curses.o rss.o shared.o -o rss-curses

rss-curses.o: rss-curses.c rss.h shared.o
	$(CC) rss-curses.c -c

shared.o: shared.c shared.h
	$(CC) shared.c -c
