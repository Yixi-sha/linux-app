#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

void main()
{
	int fd = 0;
	pid_t pid_fork = 0;
	int ret = 0;
	ssize_t size_num = 0;
	key_t signal_key = 0;
	int signal_des = 0;
	int mem_des = 0;
	void* mem_addr = NULL;
	char* rets = NULL;
	
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
			ret = strlen("yixi-sha");
			printf("yixi-sha's length is %d\n",ret);
			
			
			mem_des = shmget(signal_key,20,IPC_CREAT);
			printf("old's mem_des is %d\n",mem_des);
			mem_addr = shmat(mem_des,NULL, 0);
			printf("old's mem_addr is %p\n",mem_addr);
			
			
			sleep(1);
			
			rets = strncpy((char*)mem_addr,"yixi-sha",8);
			printf("old's rets is %p\n",rets);
			rets = strncpy((char*)mem_addr+8,"yixi-sha",8);
			printf("old's rets is %p\n",rets);
			
			
			ret = shmdt(mem_addr);
			printf("shmdt's ret is %d\n",ret);
			
			sops.sem_op = 1;
			semop(signal_des,&sops,1);
			exit(0);
		}
	else if (pid_fork == 0)
		{
			char read_buf[20];
			sops.sem_num = 0;
			sops.sem_op = -1;
			semop(signal_des,&sops,1);
			
			mem_des = shmget(signal_key, 20,IPC_CREAT);
			printf("child's mem_des is %d\n",mem_des);
			mem_addr = shmat(mem_des,NULL,0);
			printf("child's mem_addr is %p\n",mem_addr);
			
			rets = strncpy(read_buf,(char*)mem_addr,16);
			read_buf[16] = '\0';
			printf("read_buf is %s\n",read_buf);
			
			ret = system("rm *.bak");
			printf("system's ret is %d\n",ret);
			
			ret = shmdt(mem_addr);
			printf("child shmdt's ret is %d\n",ret);
			ret = shmctl(mem_des, IPC_RMID, NULL);
			printf("child shmctl's ret is %d\n",ret);
			
			
			semctl(signal_des, 1, IPC_RMID);
			exit(0);
			
		}	
	
	exit(0);
	
}