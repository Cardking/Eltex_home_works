#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#define N 10
#define BUF_SIZE 255
//#define TEST

#define MAX(a, b) a>b ? a:b

int main()
{
	int pid, status; // Process variables.
	int size_max = 0, words_num = 0; // Parsing variables.
	int i, j, k; // Iterators.
	char buf[BUF_SIZE+3]; // Buffer.
	
	// Beauty.
	printf("MyBASH|\e[0;92m%s:\e[0;94m%s\033[0m$ ",\
	 getenv("USER"), getenv("PWD"));
	// Get command line.
	fgets(buf, BUF_SIZE, stdin);
	// Get word's max length and number of words.
	for(i = 0, j = 0; buf[i] != '\0'; ++i){
		if(isspace(buf[i])){
			size_max = MAX(size_max, j);
			if(j > 0){
				words_num++;
			}
			j = 0;
			continue;
		}
		++j;
	}
	
	// Get words.
	char argv[words_num][size_max+1];
	char *argv_pointers[words_num+1];
	for(i = 0, j = 0, k = 0; buf[i] != '\0'; ++i){
		if(isspace(buf[i])){
			if(j > 0){
				argv[k][j] = '\0';
				++k;
			}
			j = 0;
			continue;
		}
		argv[k][j] = buf[i];
		++j;
	}
	for(i = 0; i < words_num; ++i){
		argv_pointers[i] = argv[i];
	}
	argv_pointers[words_num] = NULL;
	#ifdef TEST
		printf("Words:");
		for(i = 0; i < words_num; ++i){
			printf(" '%s'", argv[i]);
		}
		printf("\n");
	#endif
	
	// Command execution.
	pid = fork();
	switch(pid){
		case 0:
			execvp(argv_pointers[0], argv_pointers);
			exit(EXIT_SUCCESS);
			break;
		case -1:
			perror("ERROR");
			exit(errno);
			break;
		default:
			wait(&status);
			exit(EXIT_SUCCESS);
			break;
	}
	
	
	return 0;
}













