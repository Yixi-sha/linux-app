#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

void main(void)
{
	int fd = 0;
	/****create a new file****/
/*	fd = creat("/work/app/file/test1.c",777); */
	/****open the file****/
	fd = open("/work/app/file/test.c",O_RDWR|O_CREAT,777);
	printf("%3d\n",fd);
	/*****close flie ***********/
	fd = close(fd);
	printf("%3d\n",fd);
}