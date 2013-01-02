bitsort : bitmap.o main.o
	gcc -o bitsort bitmap.o main.o
bitmap.o : bitmap.c bitmap.h
	gcc -c bitmap.c
main.o : main.c bitmap.h
	gcc -c main.c

clean:
	rm *.o bitsort
