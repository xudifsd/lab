
OBJS = wordcount.o splaytree.o getword.o
LIBS = splaytree.h
CFLAGES = -pg -O2

wco : $(OBJS)
	gcc $(CFLAGES) -o wco $(OBJS)

wordcount.o: wordcount.c $(LIBS)
	gcc $(CFLAGES) -c wordcount.c

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
