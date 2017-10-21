#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void main()
{
	time_t time_test = 0;
	struct tm* tm_test = NULL;
	char* buf;
	int symbol = -1;
	
	struct timeval tv_test ;
	
	symbol = gettimeofday(&tv_test,NULL);
	printf("read is %d\n",symbol);
	
	buf = ctime(&(tv_test.tv_sec));
	printf("%s",buf);
	
	time_test = time(NULL);
	
	printf("time is %ld\n",tv_test.tv_sec);
	
	printf("time is %ld\n",tv_test.tv_usec);
	
	tm_test = gmtime(&time_test);
	tm_test->tm_year += 1900;
	printf("%d-%d-%d-%d-%d-%d\n",tm_test->tm_year,tm_test->tm_mon+1,tm_test->tm_mday,tm_test->tm_hour,tm_test->tm_min,tm_test->tm_sec);
	
	tm_test = localtime(&time_test);
	
	printf("%d-%d-%d-%d-%d-%d\n",tm_test->tm_year+1900,tm_test->tm_mon+1,tm_test->tm_mday,tm_test->tm_hour,tm_test->tm_min,tm_test->tm_sec);
	
	buf = asctime(tm_test);
	printf("%s",buf);
	
	
}