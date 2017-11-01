#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t thread_mutex ;
int work = 0;

void *thread_printf(void *arg)
{
	
	int ret = 0;
	int i = 0;
	
	


	for(i = 0;i<10;i++)
	{
		
		ret = pthread_mutex_lock(&thread_mutex);
		work++;
		printf("arg is %s  %d\n",(char *)arg,work);
		ret = pthread_mutex_unlock(&thread_mutex);
		sleep(1);
	}
	printf("work is %d\n",work);
	
	pthread_exit((void *)(&ret));
}



void main()
{
	int ret = 0;
	pthread_t thread_id = 0,thread_id_1 = 0;
	int *ret_thread ;
	
	ret = pthread_mutex_init(&thread_mutex,NULL);
	

	ret = pthread_create(&thread_id, NULL,thread_printf, "yixi-sha");

	
	ret = pthread_create(&thread_id_1, NULL,thread_printf, "sha-yixi");
	
	
	
	printf("**************\n");
	ret = pthread_join(thread_id,(void *)(&ret_thread));

	
	ret = pthread_join(thread_id_1,(void *)(&ret_thread));

	system("rm *.bak");
	ret = pthread_mutex_destroy(&thread_mutex);
	printf("pthread_mutex_destroy's ret is %d\n",ret);
	
	exit(0);
}