#include "data.h"

#ifndef HASH_H
#define HASH_H

struct hash_entry{
	struct data *data;
	struct hash_entry *next;	//for collision save
};

struct phone_hash_table {	//use for hash_table array
	int phone_num;	//Only save last 2 num in phone_num, namely 00~99
	struct hash_entry *head;
};

struct name_hash_table {	//use for hash_table array
	char name;	//Only save first character in name, namely a~z
	struct hash_entry *head;
};

extern struct phone_hash_table * init_phone_hash_table();
extern struct name_hash_table * init_name_hash_table();
extern struct data *insert_into_phone_hash_table(struct phone_hash_table *, struct data *);
extern struct data *insert_into_name_hash_table(struct name_hash_table *, struct data *);
extern struct data *find_by_phone(struct phone_hash_table *, long long );
extern struct data *find_by_name(struct name_hash_table *, char *);
#endif //HASH_H
