OBJS = main.o hash.o data.o
LIBS = hash.h data.h
CFLAGES =

main: $(OBJS) $(LIBS)
	gcc $(CFLAGES) -o main $(OBJS)

main.o: main.c $(LIBS)
	gcc $(CFLAGES) -c main.c

hash.o: $(LIBS)
	gcc $(CFLAGES) -c hash.c

data.o: $(LIBS)
	gcc $(CFLAGES) -c data.c

clean:
	-rm -f main $(OBJS)
