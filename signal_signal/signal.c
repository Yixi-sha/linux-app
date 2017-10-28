#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
	int fd = -1;
	pid_t pid_fork = -1;
	ssize_t size_fd = 0;
	key_t key_signal = 0;
	int sem_id = -1;
	int ret = 0;
	struct sembuf spos;
	
	/*****创建信号量*****/
	key_signal = ftok("/work/app/signal_signal",1);
	printf("key_signal is %d\n",key_signal);

	sem_id = semget(key_signal,1,IPC_CREAT|777);
	printf("semget return is %d\n",sem_id);
	semctl(sem_id,0,SETVAL,1);
	ret = semctl(sem_id,0,GETVAL);
	printf("GETVAL is %d\n",ret);
	spos.sem_flg = SEM_UNDO;
	
	pid_fork = fork();
	if (pid_fork > 0)
		{
			spos.sem_num = 0;
			spos.sem_op = -1;
			
			fd = open("/work/app/signal_signal/test",O_WRONLY|O_APPEND);
			/***获取信号量*****/
			ret = semop(sem_id,&spos,1);
			printf("ret return is %d\n",ret);
			printf("old fd is %d\n",fd);
			size_fd = write(fd,"bin",3);
			printf("old writed num is %d\n",size_fd);
			sleep(5);
			size_fd = write(fd,"gge",3);
			printf("old writed num is %d\n",size_fd);
			/*****释放信号量*****/
			spos.sem_op = 1;
			ret = semop(sem_id,&spos,1);
			printf("ret return is %d\n",ret);
			close(fd);
			exit(0);
		}
	else if(pid_fork == 0)
		{
			sleep(1);
			spos.sem_num = 0;
			spos.sem_op = -1;
			fd = open("/work/app/signal_signal/test",O_WRONLY|O_APPEND);
			printf("child fd is %d\n",fd);
			/***获取信号量*****/
			ret = semctl(sem_id,0,GETVAL);
			printf("GETVAL is %d\n",ret);
			ret = semop(sem_id,&spos,1);
			printf("ret return is %d\n",ret);
			size_fd = write(fd,"www",3);
			printf("child writed num is %d\n",size_fd);
			/*****释放信号量*****/ 
			spos.sem_op = 1;
			ret = semop(sem_id,&spos,1);
			printf("ret return is %d\n",ret);
			close(fd);
			exit(0);
		}	
}