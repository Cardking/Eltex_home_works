#include "headers/katalog.h"

// Katalog initialization:
int ktlog_init(struct katalog* ktlog){ 
	if(ktlog == NULL){ // Empty pointer ktlog check.
		return -1;
	}
	ktlog->user_arr = (struct user*)malloc(sizeof(struct user)*10); // Malloc memory for user array.
	if(ktlog->user_arr == NULL){ // Empty user array check.
		return -2;
	}
	ktlog->capacity = 10;
	ktlog->size = 0;
	
	return 0;
}
int ktlog_add(struct katalog* ktlog){
	if(ktlog == NULL){ // Empty pointer ktlog check.
		return -1;
	}
	// User array full check.
	if(ktlog->size >= ktlog->capacity){
		ktlog->user_arr = (struct user*)realloc(ktlog->user_arr\
		 ,sizeof(struct user)*ktlog->capacity*2);
		ktlog->capacity *= 2;
	}
	char number[NUM_SIZE]; // Number buffer.
	char name[NAME_SIZE]; // Name buffer.
	int i;
	char flag; // Loop out flag.
	printf("-Add-\n");
	do{
		printf("Enter the number: ");
		fgets(number, NUM_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NUM_SIZE; ++i){ // Number validation.
			if(!(number[i] >= '0' && number[i] <= '9')){
				if(number[i] == '\n'){ // \n change to end of string.
					number[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
		if(number[0] == '\0'){ // Empty input check.
			printf("Try again\n");
			flag = 1;
		}
	} while(flag);
	do{
		printf("Enter the name: ");
		fgets(name, NAME_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NAME_SIZE; ++i){ // Name validation.
			if(!((name[i] >= 'A' && name[i] <= 'Z')\
			 || (name[i] >= 'a' && name[i] <= 'z'))){
				if(name[i] == '\n'){ // \n change to end of string.
					name[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
		if(name[0] == '\0'){ // Empty input check.
			printf("Try again\n");
			flag = 1;
		}
	} while(flag);
	strcpy(ktlog->user_arr[ktlog->size].name, name);
	do{
		printf("Enter the surname: ");
		fgets(name, NAME_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NAME_SIZE; ++i){ // Surname validation.
			if(!((name[i] >= 'A' && name[i] <= 'Z')\
			 || (name[i] >= 'a' && name[i] <= 'z'))){
				if(name[i] == '\n'){ // \n change to end of string.
					name[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
		if(name[0] == '\0'){ // Empty input check.
			printf("Try again\n");
			flag = 1;
		}
	} while(flag);
	strcpy(ktlog->user_arr[ktlog->size].surname, name);
	strcpy(ktlog->user_arr[ktlog->size].number, number);
	ktlog->size++;

	return 0;
}
int ktlog_show(struct katalog* ktlog){
	if(ktlog == NULL){ // Empty pointer ktlog check.
		return -1;
	}
	int i;
	printf("Name\tSurname\tNumber\n");
	// Users output.
	for(i = 0; i < ktlog->size; ++i){
		if(ktlog->user_arr[i].number[0] == '\0'){ // User deleted check.
			continue;
		}
		printf("%s\t%s\t%s\n", ktlog->user_arr[i].name\
		 , ktlog->user_arr[i].surname, ktlog->user_arr[i].number);
	}
	//printf("\n");
	
	return 0;
}
int ktlog_delete(struct katalog* ktlog){
	if(ktlog == NULL){ // Empty ktlog check.
		return -1;
	}
	char name[NAME_SIZE];
	int i;
	char flag; // Loop out flag.
	printf("-Delete-\n");
	do{
		printf("Enter the name: ");
		fgets(name, NAME_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NAME_SIZE; ++i){ // Name validation.
			if(!((name[i] >= 'A' && name[i] <= 'Z')\
			 || (name[i] >= 'a' && name[i] <= 'z'))){
				if(name[i] == '\n'){ // \n change to end of string.
					name[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
	} while(flag);
	// User deletion.
	for(i = 0; i < ktlog->size; ++i){
		if(strcmp(name, ktlog->user_arr[i].name) == 0){
			ktlog->user_arr[i].number[0] = '\0';
			return 0;
		}
	}

	return 1;
}
int ktlog_find(struct katalog* ktlog){
	if(ktlog == NULL){ // Empty pointer ktlog check.
		return -1;
	}
	char name[NAME_SIZE]; // Name buffer.
	int i;
	char flag;
	printf("-Find-\n");
	do{
		printf("Enter the name: ");
		fgets(name, NAME_SIZE, stdin);
		flag = 0;
		for(i = 0; i < NAME_SIZE; ++i){ // Name validation.
			if(!((name[i] >= 'A' && name[i] <= 'Z')\
			 || (name[i] >= 'a' && name[i] <= 'z'))){
				if(name[i] == '\n'){ // \n change to end of string.
					name[i] = '\0';
					break;
				}
				printf("Try again\n");
				flag = 1;
				break;
			}
		}
	} while(flag);
	printf("Name\tSurname\tNumber\n");
	// User search.
	for(i = 0; i < ktlog->size; ++i){
		if(strcmp(name, ktlog->user_arr[i].name) == 0){
			if(ktlog->user_arr[i].number[0] == '\0'){ // User deleted check.
				continue;
			}
			printf("%s\t%s\t%s\n", ktlog->user_arr[i].name\
			 , ktlog->user_arr[i].surname, ktlog->user_arr[i].number);
			 return 0;
		}
	}
	//printf("\n");
	
	return 1;
}

int ktlog_free(struct katalog* ktlog){
	if(ktlog == NULL){ // Empty pointer ktlog check.
		return -1;
	}
	free(ktlog->user_arr);
}
