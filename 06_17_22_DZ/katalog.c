#include "headers/katalog.h"

int ktlog_init(struct katalog* ktlog){
	if(ktlog == NULL){
		return -1;
	}
	ktlog->user_arr = (struct user*)malloc(sizeof(struct user)*10);
	if(ktlog->user_arr == NULL){
		return -2;
	}
	ktlog->capacity = 10;
	ktlog->size = 0;
	
	return 0;
}
int ktlog_add(struct katalog* ktlog){
	if(ktlog == NULL){
		return -1;
	}
	if(ktlog->size >= ktlog->capacity){
		ktlog->user_arr = (struct user*)realloc(ktlog->user_arr ,sizeof(struct user)*ktlog->capacity*2);
		ktlog->capacity *= 2;
	}
	char number[NUM_SIZE];
	char name[NAME_SIZE];
	int i;
	char flag;
	printf("Add:\n");
	do{
		printf("Enter the number: ");
		fgets(number, NUM_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NUM_SIZE; ++i){
			if(!(number[i] >= '0' && number[i] <= '9')){
				if(number[i] == '\n'){
					number[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
	} while(flag);
	do{
		printf("Enter the name: ");
		fgets(name, NAME_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NAME_SIZE; ++i){
			if(!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z'))){
				if(name[i] == '\n'){
					name[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
	} while(flag);
	strcpy(ktlog->user_arr[ktlog->size].name, name);
	strcpy(ktlog->user_arr[ktlog->size].number, number);
	ktlog->size++;

	return 0;
}
int ktlog_show(struct katalog* ktlog){
	if(ktlog == NULL){
		return -1;
	}
	int i;
	printf("Name\tNumber\n");
	for(i = 0; i < ktlog->size; ++i){
		printf("%s\t%s\n", ktlog->user_arr[i].name, ktlog->user_arr[i].number);
	}
	printf("\n");
	
	return 0;
}
int ktlog_delete(struct katalog* ktlog){
	if(ktlog == NULL){
		return -1;
	}
	char name[NAME_SIZE];
	int i;
	char flag;
	printf("Delete:\n");
	do{
		printf("Enter the name: ");
		fgets(name, NAME_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NAME_SIZE; ++i){
			if(!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z'))){
				if(name[i] == '\n'){
					name[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
	} while(flag);

	return 0;
}
int ktlog_find(struct katalog* ktlog){
	if(ktlog == NULL){
		return -1;
	}
	char name[NAME_SIZE];
	int i;
	char flag;
	printf("Delete:\n");
	do{
		printf("Enter the name: ");
		fgets(name, NAME_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NAME_SIZE; ++i){
			if(!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z'))){
				if(name[i] == '\n'){
					name[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
	} while(flag);
	for(i = 0; i < ktlog->size; ++i){
		if(strcmp(name, ktlog->user_arr[i].name) == 0){
			printf("%s\t%s\n", ktlog->user_arr[i].name, ktlog->user_arr[i].number);
		}
	}
}
