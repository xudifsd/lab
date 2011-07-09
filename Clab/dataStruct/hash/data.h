#ifndef DATA_H
#define DATA_H

#define NAME_MAXLEN 30
#define ADDRESS_MAXLEN 100

struct data {
	long long phone_num;
	char name[NAME_MAXLEN];
	char address[ADDRESS_MAXLEN];
};

extern struct data *init_data(long long , char *, char *);
extern int judge_by_phone(struct data *, long long);
extern int judge_by_name(struct data *, char *);

#endif //DATA_H
