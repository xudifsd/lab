#include <stdio.h>
#include <stdlib.h>

/*calculate fib number*/

unsigned long long fib(unsigned long long n){
	if ( n < 2 ) {
		return n;
	}
	return fib(n-1) + fib(n-2);
}

int main(int argc, char *argv[]) {
	if ( argc != 2 ) {
		fprintf(stderr, "Usage: %s <n'th of fib>\n", argv[0]);
		exit(1);
	}
	printf("%lld\n", fib(atoi(argv[1])));
}
