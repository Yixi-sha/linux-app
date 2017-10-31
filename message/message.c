#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/msg.h>

void main()
{
	int fd = 0;
	pid_t pid_fork = 0;
	int ret = 0;
	key_t signal_key = 0;
	int signal_des = 0;
	int msg_des = 0;
	struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               char mtext[8];    /* message data */
               };
	
	struct sembuf sops;
	char *rets = NULL;
	
	
	signal_key = ftok("/work/app/message",1);
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
			struct msgbuf send_buf;
			sops.sem_num = 0;
			ret = strlen("yixi-sha");
			printf("yixi-sha's length is %d\n",ret);
			
			msg_des = msgget(signal_key,IPC_CREAT);
			printf("old's msg_des is %d\n",msg_des);
			
			sleep(1);
			
			send_buf.mtype = 1;
			rets = strncpy(send_buf.mtext,"yixi-sha",8);
			printf("rets is %p\n",rets);
			ret = msgsnd(msg_des,&send_buf,8,0);
			printf("send's ret is %d\n",ret);
			
			send_buf.mtype = 1;
			rets = strncpy(send_buf.mtext,"sha-yixi",8);
			printf("rets is %p\n",rets);
			ret = msgsnd(msg_des,&send_buf,8,0);
			printf("old send's ret is %d\n",ret); 
			
			
			
			sops.sem_op = 1;
			semop(signal_des,&sops,1);
			
		
			exit(0);
		}
	else if (pid_fork == 0)
		{
			sops.sem_num = 0;
			sops.sem_op = -1;
			semop(signal_des,&sops,1);
			
	    ret = system("rm *.bak");
			printf("system's ret is %d\n",ret); 
			 
			struct msgbuf read_buf;
			ssize_t read_size = 0;
			
			msg_des = msgget(signal_key,IPC_CREAT);
			printf("child's msg_des is %d\n",msg_des);
			
			read_size = msgrcv(msg_des,&read_buf,8,1,0);
			printf("read_size is %d\n",read_size);
			printf("read_buf is %s\n",read_buf.mtext);
			printf("read_buf is %ld\n",read_buf.mtype);
			
			
			
			ret = msgctl(msg_des,IPC_RMID, NULL);
			printf("delate's ret is %d\n",ret);
			
			
			
			
			semctl(signal_des, 1, IPC_RMID);
			exit(0);
			
		}	
	
	exit(0);
	
}