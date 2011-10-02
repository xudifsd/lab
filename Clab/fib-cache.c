#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*calculate fib number with cache*/

static unsigned long long *cache = NULL;

unsigned long long fib_cache(unsigned long long n){
	if ( n < 2 )
		return n;
	if ( cache == NULL ) {
		cache = calloc(n - 1, sizeof(unsigned long long));
		memset(cache, n - 1, 0);
	}
	if ( cache[n - 2] == 0 )
		cache[n - 2] = fib_cache(n-1) + fib_cache(n-2);
	return cache[n - 2];
}

int main(int argc, char *argv[]) {
	if ( argc != 2 ) {
		fprintf(stderr, "Usage: %s <n'th of fib>\n", argv[0]);
		exit(1);
	}
	printf("%lld\n", fib_cache(atol(argv[1])));
}
