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

int main()
{
	int pid, pnum, status;
	
	// Parent and child.
	pid = fork();
	switch(pid){
		case 0:
			pnum = 2;
			printf("%d: pid - %d | ppid - %d\n", pnum, getpid(), getppid());
			exit(EXIT_SUCCESS);
			break;
		case -1:
			perror("ERROR");
			exit(errno);
			break;
		default:
			pnum = 1;
			printf("%d: pid - %d | ppid - %d\n", pnum, getpid(), getppid());
			pid = wait(&status);
			if(pid < 0){
				perror("ERROR");
				exit(errno);
			}
			printf("%d: Completed child process - %d\n", pnum, pid);
			break;
	}
	
	return 0;
}













