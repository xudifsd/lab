#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>	/*for UINT_MAX*/
#include "heaptree.h"

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

static void abstract(const struct node *cur){
	/*abstract top*/
	static int times = 0;
	if (times < ARR_SIZE){	/*fill it up*/
		top[times].word = cur->word;
		top[times].count = cur->count;
		times++;
	} else{
		int min = minest();
		if (top[min].count < cur->count){
			top[min].word = cur->word;
			top[min].count = cur->count;
		}
	}
}

static void todot(const struct node *cur){
	if (cur->left != NULL){
		fprintf(stderr, "\t\"%s\\n%d\" -> \"%s\\n%d\"[headport=n, tailport=sw]\n", cur->word, cur->count, cur->left->word, cur->left->count);
	}
	if (cur->right != NULL){
		fprintf(stderr, "\t\"%s\\n%d\" -> \"%s\\n%d\"[headport=n, tailport=se]\n", cur->word, cur->count, cur->right->word, cur->right->count);
	}
}

static int marrowcmp(const void *a, const void *b){
	struct marrow *ma = (struct marrow *)a;
	struct marrow *mb = (struct marrow *)b;
	return mb->count - ma->count;
}

static void print(const char *word, const int count){
	//printf("debug:%-15s %d\n", word, count);
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
	fprintf(stdout, "Run time is %.2f ms\n",(finsih-start)/1000);
	fprintf(stdout, "depth is %d\n", traverse(root->head, NULL));
	/*following line is code for generate dot file*/
	fprintf(stderr, "digraph heaptree{\n");
	traverse(root->head, todot);
	fprintf(stderr, "}\n");
	/*above line is code for generate dot file*/
	return 0;
}
