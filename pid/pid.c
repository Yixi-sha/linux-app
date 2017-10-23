#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include  <stdlib.h>
#include <sys/wait.h>

void main()
{
	int p_pid = 0;
	
	int vf_pid = 1;
	p_pid = getpid();
	printf("pid is %d\n",p_pid);
	
	p_pid = getppid();
	printf("ppid is %d\n",p_pid);
	
	
	
/*	p_pid = vfork();*/
	p_pid = fork();
	if(p_pid == 0)
		{
			vf_pid =100;
			printf("I am child ");
			p_pid = getpid();
	    printf("pid is %d\n",p_pid);		
	    exit(3); 
		}	
	if(p_pid == -1)
		printf("fail\n");
	else if(p_pid > 0);
		{
			int ret = -1;
			pid_t  wait_pid = -1;
			wait_pid = wait(&ret);
			printf("ret is %d\n",ret);
			printf("wait_pidt is %d\n",wait_pid);
			printf("i am old ");
			p_pid = getpid();
	    printf("pid is %d\n",p_pid);
	    printf("vf_pid is %d\n",vf_pid);
	    ret = system("rm *.bak");
	    printf("ret is %d\n",ret);
	    ret = system("ls");
	    printf("ret is %d\n",ret);
/*	    execl("/work/app/pid/hello","hello",(char *)0); */
	    exit(0);    
		}	
		
}