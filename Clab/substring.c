#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <malloc.h>

/*
 * This program is defined in <Programming Peal> 15.2,
 * it find the longest repeated substring in a text file
 * */

int pstrcmp(const void *a, const void *b){
	return strcmp(*(char **)a,  *(char **)b);
}

int comlen(const char *a, const char *b){
	int i;
	for (i = 0; (*(a + i) != '\0') && (*(b + i) != '\0'); i++){
		if (*(a+i) != *(b+i))
			return i;
	}
	return i;
}

int main(int argc, char *argv[]){
	int fd;
	if (argv[1])
		fd = open(argv[1], O_RDONLY);
	else{
		fprintf(stderr, "Usage: ./a.out filename");
		exit(1);
	}
	struct stat st;
	fstat(fd, &st);
	char *content = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	char **a = (char **)malloc(sizeof(char *) * st.st_size);
	int i;
	for (i = 0; i < st.st_size; i++){
		a[i] = content+i;
	}
	qsort(a, st.st_size, sizeof(char *), pstrcmp);
	int maxlen = 0;
	int maxi = 0;
	for (i = 0; i< st.st_size - 1; i++){
		int len = comlen(a[i], a[i+1]);
		if (len > maxlen){
			maxlen = len;
			maxi = i;
		}
	}
	printf("Max is '%.*s'\n", maxlen, a[maxi]);
}
