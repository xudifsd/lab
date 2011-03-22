bitsort : bitmap.o main.o
	cc -o bitsort bitmap.o main.o
bitsort.o :	bitmap.c bitmap.h
	cc -c bitmap.c
main.o : main.c bitmap.h
	cc -c main.c
