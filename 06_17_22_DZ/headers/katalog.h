#ifndef KATALOG_H
#define KATALOG_H 1

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define NUM_SIZE 11
#define NAME_SIZE 32

struct user{
	char number[NUM_SIZE];
	char name[NAME_SIZE];
	char surname[NAME_SIZE];
};

struct katalog{
	unsigned int size;
	unsigned int capacity;
	struct user* user_arr;
};

int ktlog_init(struct katalog* ktlog);
int ktlog_add(struct katalog* ktlog);
int ktlog_show(struct katalog* ktlog);
int ktlog_delete(struct katalog* ktlog);
int ktlog_find(struct katalog* ktlog);
int ktlog_free(struct katalog* ktlog);

#endif
