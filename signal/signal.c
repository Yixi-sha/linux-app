#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

void signal_press(int signal_int)
{
	printf("signal is %d\n",signal_int);
}
void main()
{
	pid_t pid_fork = -1;
	pid_fork = fork();
	int ret = -1;
	
	if (pid_fork == 0)
		{
			signal(SIGINT,signal_press);
			pause();
			printf("i am child\n");
			exit(0);
		}
	if(pid_fork > 0)
		{
			sleep(1);
			printf("pid is %d\n",pid_fork);
			ret = kill(pid_fork,SIGINT);
			printf("ret is %d\n",ret);
			exit(0);
		}
}