#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define N 10
#define BUF_SIZE 50
//#define TEST

int main()
{
	int pid, status;
	int i;
	// Tree route. 
	char path[3][3] = {{'1', '\0', '\0'},\
	 {' ', ' ', '\0'}, {' ', ' ', '\0'}};
	
	// Left branch.
	printf("%s%s%s: pid - %d | ppid - %d\n",\
	 path[0], path[1], path[2], getpid(), getppid());
	pid = fork();
	switch(pid){
		case 0:
			path[1][0] = '-', path[1][1] = '2', path[1][2] = '\0';
			
			printf("%s%s%s: pid - %d | ppid - %d\n",\
			 path[0], path[1], path[2], getpid(), getppid());
			pid = fork();
			switch(pid){
				case 0:
					path[2][0] = '-', path[2][1] = '4', path[2][2] = '\0';
					
					printf("%s%s%s: pid - %d | ppid - %d\n",\
					 path[0], path[1], path[2], getpid(), getppid());
					exit(EXIT_SUCCESS);
					break;
				case -1:
					perror("ERROR");
					exit(errno);
					break;
				default:
					
					pid = wait(&status);
					if(pid < 0){
						perror("ERROR");
						exit(errno);
					}
					#ifdef TEST
						printf("%s%s%s: Ñompleted process - %d\n",\
						 path[0], path[1], path[2], pid);
					#endif
					break;
			}
			exit(EXIT_SUCCESS);
			break;
		case -1:
			perror("ERROR");
			exit(errno);
			break;
		default:
			break;
	}
	
	// Right branch.
	pid = fork();
	switch(pid){
		case 0:
			path[1][0] = '-', path[1][1] = '3', path[1][2] = '\0';
			
			printf("%s%s%s: pid - %d | ppid - %d\n",\
	 		 path[0], path[1], path[2], getpid(), getppid());
			pid = fork();
			switch(pid){
				case 0:
					path[2][0] = '-', path[2][1] = '5', path[2][2] = '\0';
					
					printf("%s%s%s: pid - %d | ppid - %d\n",\
					 path[0], path[1], path[2], getpid(), getppid());
					exit(EXIT_SUCCESS);
					break;
				case -1:
					perror("ERROR");
					exit(errno);
					break;
				default:		
					break;
			}
			pid = fork();
			switch(pid){
				case 0:
					path[2][0] = '-', path[2][1] = '6', path[2][2] = '\0';
					
					printf("%s%s%s: pid - %d | ppid - %d\n",\
					 path[0], path[1], path[2], getpid(), getppid());
					exit(EXIT_SUCCESS);
					break;
				case -1:
					perror("ERROR");
					exit(errno);
					break;
				default:		
					break;
			}
			for(i = 0; i < 2; ++i){
				pid = wait(&status);
				if(pid < 0){
					perror("ERROR");
					exit(errno);
				}
				#ifdef TEST
					printf("%s%s%s: Ñompleted process - %d\n",\
					 path[0], path[1], path[2], pid);
				#endif
			}
			exit(EXIT_SUCCESS);
			break;
		case -1:
			perror("ERROR");
			exit(errno);
			break;
		default:		
			break;
	}
	
	for(i = 0; i < 2; ++i){
		pid = wait(&status);
		if(pid < 0){
			perror("ERROR");
			exit(errno);
		}
		#ifdef TEST
			printf("%s%s%s: Ñompleted process - %d\n",\
			 path[0], path[1], path[2], pid);
		#endif
	}
	
	return 0;
}













