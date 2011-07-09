#include "hash.h"
#include <malloc.h>
#include <string.h>

/*
 *
 * There are two kinds of hash_table: phone_hash_table and name_hash_table,
 * either of them are array, this is for speed need, because it is a array,
 * we can use binary search to search hash_table. we use the same way to
 * solve collision problem, that is list, I think it is the best and most
 * convenient way to do this.
 * */

struct phone_hash_table * init_phone_hash_table(){	//init hash_table array
	int i;
	struct phone_hash_table *p;
	struct phone_hash_table *rtn = (struct phone_hash_table *)malloc((sizeof(struct phone_hash_table)) * 100);	//phone_num's range is 00~99
	for (i = 0, p = rtn; i < 100; i++, p++){	//init phone_hash_table
		p->phone_num = i;
		p->head = NULL;
	}
	return rtn;
}

struct name_hash_table * init_name_hash_table(){	//init hash_table array
	int i;
	struct name_hash_table *p;
	struct name_hash_table * rtn = (struct name_hash_table *)malloc((sizeof(struct name_hash_table)) * 26);	//name's range is a~z
	for (i = 0, p = rtn; i < 26; i++, p++){	//init name_hash_table
		p->name = 'a' + i;
		p->head = NULL;
	}
	return rtn;
}

struct data *insert_into_phone_hash_table(struct phone_hash_table *hash_table, struct data *entry){
	int start = 0;
	int end = 99;
	int target;

	struct hash_entry * new_entry = (struct hash_entry *)malloc(sizeof(struct hash_entry));	//create new entry firstly
	new_entry->data = entry;
	new_entry->next = NULL;

	int table_target = (entry->phone_num) % 100;	//hash_table formate of phone_num
	for (target = (start + end)/2; start < end; target = (start + end)/2){	//binary search
		if (table_target == (hash_table + target)->phone_num){
			break;
		} else if (table_target > (hash_table + target)->phone_num){
			start = target + 1;
		} else{
			end = target;
		}
	}
	if (start > end){	//not even found in hash_table, strange
		return NULL;
	} else {
		struct hash_entry *list_head = (hash_table + target)->head;
		struct hash_entry *p = list_head;
		if (p == NULL){	//no entry in this hash_entry
			(hash_table + target)->head = new_entry;
			return entry;	//insert successfully
		}
		for (p = list_head ; p->next != NULL; p = p->next);	//if there already have, then list them
			/*Nothing here*/
		p->next = new_entry;
		return entry;	//insert successfully
	}
}

struct data *insert_into_name_hash_table(struct name_hash_table *hash_table, struct data *entry){
	int start = 0;
	int end = 99;
	int target;
	int table_target = *(entry->name);	//hash_table formate of name

	struct hash_entry * new_entry = (struct hash_entry *)malloc(sizeof(struct hash_entry));	//create new entry firstly
	new_entry->data = entry;
	new_entry->next = NULL;

	for (target = (start + end)/2; start < end; target = (start + end)/2){	//binary search
		if (table_target == (hash_table + target)->name){
			break;
		} else if (table_target > (hash_table + target)->name){
			start = target + 1;
		} else{
			end = target;
		}
	}
	if (start > end){	//not even found in hash_table, strange
		return NULL;
	} else {
		struct hash_entry *list_head = (hash_table + target)->head;
		struct hash_entry *p = list_head;
		if (p == NULL){	//no entry in this hash_entry
			(hash_table + target)->head = new_entry;
			return entry;	//insert successfully
		}
		for (p = list_head ; p->next != NULL; p = p->next);	//if there already have, then list them
			/*Nothing here*/
		p->next = new_entry;
		return entry;	//insert successfully
	}
}

struct data *find_by_phone(struct phone_hash_table *hash_table, long long phone_num){
	int start = 0;
	int end = 99;
	int target;
	int table_target = phone_num % 100;	//hash_table formate of phone_num
	for (target = (start + end)/2; start < end; target = (start + end)/2){	//binary search
		if (table_target == (hash_table + target)->phone_num){
			break;
		} else if (table_target > (hash_table + target)->phone_num){
			start = target + 1;
		} else{
			end = target;
		}
	}
	if (start > end){	//not even found in hash_table, strange
		return NULL;
	} else {
		struct hash_entry *list_head = (hash_table + target)->head;
		struct hash_entry *p;
		if (p == NULL){	//no entry in this hash_entry
			return NULL;
		}
		for (p = list_head ; p != NULL; p = p->next){
			if (p->data->phone_num == phone_num)
				return p->data;
		}
		return NULL;//not found in hash_table
	}
}

struct data *find_by_name(struct name_hash_table *hash_table, char *name){
	int start = 0;
	int end = 99;
	int target;
	int table_target = *name;	//hash_table formate of name
	for (target = (start + end)/2; start < end; target = (start + end)/2){	//binary search
		if (table_target == (hash_table + target)->name){
			break;
		} else if (table_target > (hash_table + target)->name ){
			start = target + 1;
		} else{
			end = target;
		}
	}
	if (start > end){	//not even found in hash_table, strange
		return NULL;
	} else {
		struct hash_entry *list_head = (hash_table + target)->head;
		struct hash_entry *p;
		if (p == NULL){	//no entry in this hash_entry
			return NULL;
		}
		for (p = list_head ; p != NULL; p = p->next){
			if (!strcmp(p->data->name, name))
				return p->data;
		}
		return NULL;//not found in hash_table
	}
}
