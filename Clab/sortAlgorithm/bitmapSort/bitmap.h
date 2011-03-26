#define SUCCESS 0
#define OVERFLOW 1
#define MEMORY_NOT_ENOUGH 2

struct repository {
	int size;
	char *buffer;
	char *byteOffset;	//for getint()
	unsigned short bitOffset;	//for getint()
};

extern int initRepository(struct repository *, unsigned int);
extern int add(struct repository *, unsigned int);
extern int getint(struct repository *);
