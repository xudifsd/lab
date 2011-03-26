#define SUCCESS 0
#define OVERFLOW 1
#define MEMORY_NOT_ENOUGH 2
#define ALREADY_EXIST 3
#define NEGATIVE_ARGUMENT 4
//Below is for check()
#define EMPTY_REPOSITORY 5
#define EXHAUST_REPOSITORY 6	//if repository.byteOffset is NULL
#define WRONG_REPOSITORY 7	//if repository.bitOffset is not in range(0,CHAR_BIT+1)

struct repository {
	int size;
	char *buffer;
	char *byteOffset;	//for getint()
	unsigned short bitOffset;	//for getint()
};

extern int initRepository(struct repository *, int);
extern int add(struct repository *, int);
extern int check(struct repository *);
extern int getint(struct repository *);
