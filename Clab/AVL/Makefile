
OBJS = main.o splaytree.o getword.o
LIBS = splaytree.h
CFLAGES = -pg

wco : $(OBJS)
	gcc $(CFLAGES) -o wco $(OBJS)

main.o: main.c $(LIBS)
	gcc $(CFLAGES) -c main.c

splaytree.o : splaytree.c $(LIBS)
	gcc $(CFLAGES) -c splaytree.c

getword.o : getword.c
	gcc $(CFLAGES) -c getword.c

profile:
	cat full.txt | ./wco
	gprof wco gmon.out | less

run:
	cat full.txt | ./wco

clean :
	rm $(OBJS) wco
