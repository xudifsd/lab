#include <string.h>
#include <malloc.h>
#include "heaptree.h"

/*
 * when THRESHOLD is reached in count, this node will be considered as a frequent visited node,
 * so we improve the position of this node, improve it until it's father node's count is more,
 * so this tree sometime like heap.
 * */
#define THRESHOLD 3

inline struct root * init_root(){
	struct root *rtn = malloc(sizeof(struct root));
	memset(rtn, 0, sizeof(struct root));
	return rtn;
}

inline struct node * init_node(char *word){
	struct node *rtn = malloc(sizeof(struct node));
	memset(rtn, 0, sizeof(struct node));
	rtn->word = strdup(word);
	rtn->count = 1;
	return rtn;
}

int traverse(struct node *cur, void (*fun)(const struct node *)){	/*traverse reutrn the depth of cur*/
	if (cur == NULL)
		return 0;
	int l,r;
	l = traverse(cur->left, fun);
	if (fun)
		fun(cur);
	r = traverse(cur->right, fun);
	return ((l > r)? l : r) + 1;
}

static inline struct node * improveLeft(struct node *k2){
	struct node *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	return k1;
}

static inline struct node * improveRight(struct node *k2){
	struct node *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	return k1;
}

struct node *insert(struct node *cur, char *word){
	/*this is heap like tree*/
	if (cur == NULL){
		return init_node(word);
	}
	int r = strcmp(cur->word, word);
	if (r == 0){
		cur->count++;
	} else if(r > 0){
		cur->left = insert(cur->left, word);
		if ((cur->left->count > THRESHOLD) && (cur->left->count > cur->count)){
			cur = improveLeft(cur);
		}
	} else{
		cur->right = insert(cur->right, word);
		if ((cur->right->count > THRESHOLD) && (cur->right->count > cur->count)){
			cur = improveRight(cur);
		}
	}
	return cur;
}
