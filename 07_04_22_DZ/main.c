#include <unistd.h>
#include <sys/types.h>
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
	int in_file_fd = 0;
	char buf[BUF_SIZE+3];
	int str_size;
	long int bytes_written, bytes_read;
	long int i; //Iterators.
	
	in_file_fd = open("in_file.txt", O_CREAT | O_RDWR | O_TRUNC);
	if(in_file_fd < 0){
		perror("ERROR");
		exit(errno);
	}
	
	printf("\nEnter string: ");
	fgets(buf, BUF_SIZE, stdin);
	str_size = strlen(buf);
	if(buf[str_size-1] == '\n'){
		--str_size;
	}
	bytes_written = write(in_file_fd, buf, str_size);
	printf("Bytes_written: %ld\n", bytes_written);
	
	struct stat stat_buf;
	fstat(in_file_fd, &stat_buf);
	
	bytes_read = read(in_file_fd, buf, stat_buf.st_size);
	printf("Bytes_read: %ld\n", bytes_read);
	buf[stat_buf.st_size] = '\0';
	printf("Readed direct: \"%s\"\n", buf);
	
	for(i = stat_buf.st_size-1; i >= 0; --i){
		lseek(in_file_fd, i, 0);
		bytes_read = read(in_file_fd, buf + (stat_buf.st_size-1-i), 1);
	}
	buf[stat_buf.st_size] = '\0';
	printf("Readed reverse: \"%s\"\n", buf);
	printf("\n\n");
	
	close(in_file_fd);
	return 0;
}













