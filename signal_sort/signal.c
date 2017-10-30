#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
	int fd = 0;
	pid_t pid_fork = 0;
	int ret = 0;
	ssize_t size_num = 0;
	key_t signal_key = 0;
	int signal_des = 0;
	
	struct sembuf sops;
	
	signal_key = ftok("/work/app/signal_sort",1);
	printf("signal_key is %d\n",signal_key);
	signal_des = semget(signal_key,1,IPC_CREAT);
	printf("signal_des is %d\n",signal_des);
	ret = semctl(signal_des,0,SETVAL,0);
	printf("semctl's ret is %d\n",ret);
	ret = semctl(signal_des,0,GETVAL);
	printf("semctl's ret is %d\n",ret);
	sops.sem_flg = SEM_UNDO;
	
	pid_fork = fork();
	if (pid_fork > 0)
		{
			sops.sem_num = 0;
			fd = open("/work/app/signal_sort/test",O_RDWR);
			printf("fd is %d\n",fd);
			if (fd == -1)
				{
					fd = open("/work/app/signal_sort/test",O_RDWR|O_CREAT,777);
					printf("fd is %d\n",fd);
				}
			sleep(1);
			size_num = write(fd,"yixi-sha",8);
			printf("write's size_num is %d\n",size_num);
			ret = close(fd);
			printf("close's ret is %d\n",ret);
			sops.sem_op = 1;
			semop(signal_des,&sops,1);
			exit(0);
		}
	else if (pid_fork == 0)
		{
			char read_buf[10];
			sops.sem_num = 0;
			sops.sem_op = -1;
			semop(signal_des,&sops,1);
			fd = open("/work/app/signal_sort/test",O_RDWR);
			printf("child fd is %d\n",fd);
			size_num = read(fd,read_buf,8);
			read_buf[size_num] = '\0';
			printf("child read's size_num is %d\n",size_num);
			printf("child read_buf  is %s\n",read_buf);
			ret = ftruncate(fd, 0);
			printf("child ftruncate's ret is %d\n",ret);
			ret = close(fd);
			printf("child close's ret is %d\n",ret);
			ret = system("rm *.bak");
			printf("system's ret is %d\n",ret);
			exit(0);
			
		}	
	
	exit(0);
	
}