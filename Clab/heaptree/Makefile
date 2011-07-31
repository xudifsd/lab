
OBJS = main.o heaptree.o getword.o
LIBS = heaptree.h
CFLAGES = -pg -O2

wco : $(OBJS)
	gcc $(CFLAGES) -o wco $(OBJS)

main.o: main.c $(LIBS)
	gcc $(CFLAGES) -c main.c

heaptree.o : heaptree.c $(LIBS)
	gcc $(CFLAGES) -c heaptree.c

getword.o : getword.c
	gcc $(CFLAGES) -c getword.c

profile:
	cat full.txt | ./wco
	gprof wco gmon.out | less

run:
	cat full.txt | ./wco

clean :
	rm $(OBJS) wco
