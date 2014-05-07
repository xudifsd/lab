CFLAGS = -Wall -g -c
OBJS = skiplist.o
HEADER = skiplist.h

main: main.o $(OBJS)
	gcc -o main main.o $(OBJS)

main.o: main.c $(HEADER)
	gcc $(CFLAGS) main.c

skiplist.o: skiplist.c $(HEADER)
	gcc $(CFLAGS) skiplist.c

clean:
	-rm *.o main
