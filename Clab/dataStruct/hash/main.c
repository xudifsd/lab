#include "data.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

struct data *user_input(){
	long long phone_num;
	char name[NAME_MAXLEN];
	char address[ADDRESS_MAXLEN];
	printf("Please input phone number, input 0 for break boring loop:");
	scanf("%lld", &phone_num);
	if (phone_num == 0){
		return NULL;
	}
	printf("Please input name:");
	scanf("%s", name);
	printf("Please input address:");
	scanf("%s", address);
	return init_data(phone_num, name, address);
}

struct data * search_by_phone(struct phone_hash_table *phone_table){
	long long phone_num;
	printf("Please input phone_num you want search:");
	scanf("%lld", &phone_num);
	return find_by_phone(phone_table, phone_num);
}

struct data * search_by_name(struct name_hash_table *name_table){
	char name[NAME_MAXLEN];
	printf("Please input name you want search:");
	scanf("%s", name);
	return find_by_name(name_table, name);
}

void print_data(struct data *entry){
	printf("Name:%s\nPhone Number:%lld\nAddress:%s\n",entry->name, entry->phone_num, entry->address);
	fflush(stdout);
}

int main(int argc, char *argv[]){
	/*
	 * We save 2 hash_table: phone_hash_table and name_hash_table,
	 * every time user input new entry, we save it in either 
	 * hash_table, so that we can search it by name, or search it
	 * by phone_num.
	 * */
	struct phone_hash_table *phone_table = init_phone_hash_table();
	struct name_hash_table *name_table = init_name_hash_table();
	struct data * entry;
	while (1){
		entry = user_input();
		if (entry == NULL){
			break;
		}
		insert_into_phone_hash_table(phone_table, entry);
		insert_into_name_hash_table(name_table, entry);
	}
	int option;
	while (1){
		struct data *entry;
		printf("option:1 for exit, 2 for search by phone, 3 for search by name\n");
		scanf("%d",&option);
		switch (option){
			case 1 : exit(0);
			case 2 : entry = search_by_phone(phone_table);break;
			case 3 : entry = search_by_name(name_table);break;
		}
		if (entry != NULL){
			print_data(entry);
		}else{
			printf("Not found!\n");
		}
	}
}
