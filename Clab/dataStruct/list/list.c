#include<string.h>
#include<malloc.h>
#include"list.h"

root * ListInit(){
	root *result = (root *)malloc(sizeof(root));
	result->sum=0;
	result->head=NULL;
	return result;
}//ListInit

static node * ListNodeInit(char *word){
	node *result=(node *)malloc(LEN);
	result->count=1;
	strcpy(result->word,word);
	result->next=NULL;
}//ListNodeInit

int ListInsert(root *operator,char *word){
	node *p=NULL;
	if( operator->sum == 0 ){	//empty set
		operator->head = ListNodeInit(word);
		operator->sum++;
		return 0;
	}
	else{
		for( p=operator->head ; strcmp(p->word,word)!=0 && p->next!=NULL ; p=p->next ){}
		if( strcmp(p->word,word)==0 ){
			p->count++;
			operator->sum++;
			return 0;
		}
		else{
			p->next = ListNodeInit(word);
			operator->sum++;
			return 0;
		}
	}
}//ListInsert

int ListDelete(root *operator,char *word){
	node *p1=NULL; node *p2=NULL;
	if( operator->sum == 0 ){	//empty set
		return 1;	//error : empty set
	}
	else{
		if( strcmp(operator->head->word,word) == 0 ){	//the first node is what should be deleted
			p1 = operator->head;
			operator->head = p1->next;
			operator->sum -= p1->count;
			free(p1);
		}
		else{
			for( p1=p2=operator->head ; strcmp(p1->word,word)!=0 && p1->next!=NULL ; p2=p1,p1=p1->next ){}
			if( strcmp(p1->word,word)==0 ){	//p1 now is pointing what should be deleted
				p2->next=p1->next;
				operator->sum -= p1->count;
				free(p1);
			}
			else{
				return 2;	//error : not found
			}
		}
	}
}//ListDelete

void ListPrintall(root *operator){	//for test usage
	node *p=NULL;
	if( operator->sum==0 ){
		printf("Empty set!\n");
		return;
	}
	else{
		printf("Sum is %d\n",operator->sum);
		for( p=operator->head ; p!=NULL ; p=p->next ){
			printf("%d\t%s\n",p->count,p->word);
		}
	}
}//ListPrintall
