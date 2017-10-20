#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

void main(void)
{
	
/*****init*******/	
	int fd = 0,fd_cpoy=0;
	char buf_read[10] ;
	char buf_write[10] = {"abcde12345"};
	ssize_t count = 0;
	int off_t = -2;
	
	/****create a new file****/
	
/*	fd = creat("/work/app/file/test1.c",777); */
	
	/****open the file****/
	
	fd = open("/work/app/file/test.c",O_RDWR|O_CREAT,777);
	printf("open %d\n",fd);
	
	/******write the file***********/

	
	
	count = write(fd, buf_write, 10);
	printf("write %d \n",count);
	printf("write_buf %s\n",buf_write);		
	/*******read the file and set offset*****/
	off_t = lseek(fd, 0, SEEK_SET);
	printf("offset %d \n",off_t);
	
	count = read(fd, buf_read, 5);
	printf("read %d",count);
	buf_read[count] = '\0';
	printf("read_buf %s\n",buf_read);
	
	/*****copy fd*******/
	fd_cpoy = dup(fd);
	
	printf("open %d\n",fd_cpoy);
	count = read(fd_cpoy, buf_read, 5);
	printf("read1 %d",count);
	buf_read[count] = '\0';
	printf("read_buf1 %s\n",buf_read);
	
 /*****close flie ***********/
	
	fd = close(fd);
	printf("%d\n",fd);  
}