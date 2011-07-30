#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>	/*for UINT_MAX*/
#include "splaytree.h"

#define MAX 30
#define ARR_SIZE 10

struct marrow top[ARR_SIZE];

static int minest(){	/*find minest in top*/
	unsigned int count = UINT_MAX;
	unsigned int mini;
	int i;
	for (i = 0; i < ARR_SIZE; i++){
		if (top[i].count < count){
			count = top[i].count;
			mini = i;
		}
	}
	return mini;
}

static void abstract(const char *word, const int count){
	/*abstract top*/
	static int times = 0;
	if (times < ARR_SIZE){	/*fill it up*/
		top[times].word = word;
		top[times].count = count;
		times++;
	} else{
		int min = minest();
		if (top[min].count < count){
			top[min].word = word;
			top[min].count = count;
		}
	}
}

static int marrowcmp(const void *a, const void *b){
	struct marrow *ma = (struct marrow *)a;
	struct marrow *mb = (struct marrow *)b;
	return mb->count - ma->count;
}

static void print(const char *word, const int count){
	printf("debug:%-15s %d\n", word, count);
}

int main(int argc, char *argv[]){
	double start,finsih;
	char word[MAX];
	start=(double)clock();
	struct root *root = init_root();
	while((getword(word)) != EOF) {
		root->head = insert(root->head, word);
		root->sum ++ ;
	}
	traverse(root->head, abstract);
	qsort(top, ARR_SIZE, sizeof(struct marrow), marrowcmp);
	int i;
	for (i = 0; i < ARR_SIZE; i++){
		printf("%-15s %d\n", top[i].word, top[i].count);
	}
	printf("There are %d words.\n",root->sum);
	finsih=(double)clock();
	fprintf(stderr, "Run time is %.2f ms\n",(finsih-start)/1000);
	fprintf(stderr, "depth is %d\n", traverse(root->head, NULL));
	//traverse(root->head, print);
	return 0;
}
