#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE


void main()
{
	int pipe_fd[2];
	int ret = -1;
	int fd_pid = -1;
	ssize_t pipe_size = 0;
	char read_buf[10];
	
	ret = pipe(pipe_fd);
	printf("ret is %d\n",ret);
	printf("pipe_fd[0] is %d\n",pipe_fd[0]);
	printf("pipe_fd[1] is %d\n",pipe_fd[1]);
	
	fd_pid = fork();
	if(fd_pid > 0)
		{
			pipe_size = read(pipe_fd[0], read_buf, 5);
			ret = close(pipe_fd[0]);
			printf("read ret is %d\n",ret);
			printf("read pipe_size is %d\n",pipe_size);
			read_buf[pipe_size] = '\0';
			printf("read char* is %s\n",read_buf);
			exit(0); 
		}
	else if(fd_pid == 0)
		{
			pipe_size = write(pipe_fd[1], "12345", 5);
			ret = close(pipe_fd[1]);
			printf("write ret is %d\n",ret);
			printf("write pipe_size is %d\n",pipe_size);
			exit(0);
		}
	
	exit(0);
}