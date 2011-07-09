#include "data.h"
#include <string.h>
#include <malloc.h>

struct data * init_data(long long phone_num, char *name, char *address){	//util for malloc struct data and init it
	struct data *rtn = (struct data *)malloc(sizeof(struct data));
	rtn->phone_num = phone_num;
	strcpy(rtn->name, name);
	strcpy(rtn->address, address);
	return rtn;
}

int judge_by_phone(struct data *entry, long long phone_num){
	return (entry->phone_num == phone_num);
}

int judge_by_name(struct data *entry, char *name){
	return (!strcmp(entry->name, name));
}
