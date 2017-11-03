#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>


#define TCP_port 3333

void main()
{
	int fd_socket = 0;
	int ret = 0;
	/******����TCP*****/
	
	in_addr_t TCP_addr = 0;
	struct sockaddr_in  TCP_stuct,TCP_accept;
	char *TCP_addrs = NULL;
	socklen_t socker_len = 0;
	
	char read_buf[128];
	
	system("rm *.bak");
	
	size_t read_size = 0;
	
	
	
	/*******����IPV4 TCP�׽���******/ 
	
	fd_socket = socket(AF_INET,SOCK_DGRAM ,0);
	printf("socket's fd_socket is %d\n",fd_socket);
	if(fd_socket == -1)
		{
			exit(0);
		}
	
	
	
	/******�󶨶˿�*************/
	
		/****ת����ַ*******/
	bzero(&TCP_stuct,sizeof(struct sockaddr));
	
	
	TCP_stuct.sin_addr.s_addr = htonl(INADDR_ANY);
	TCP_addrs = inet_ntoa(TCP_stuct.sin_addr);
	printf("ip is %s\n",TCP_addrs);
	
	TCP_stuct.sin_port = htons(TCP_port);
	TCP_stuct.sin_family = AF_INET;
	ret = bind(fd_socket,(struct sockaddr *)(&TCP_stuct),sizeof(struct sockaddr));
	printf("bind's ret is %d\n",ret);
	printf("ip is %d\n",TCP_stuct.sin_addr.s_addr);
	if(ret == -1)
		{
			exit(0);
		}
	

	while(1)
	{
		  
	/***********��������***************/
		read_size = recvfrom(fd_socket,read_buf,128,0,(struct sockaddr *)(&TCP_accept),&socker_len);
		printf("accept's ip is %s\n",inet_ntoa((struct in_addr)TCP_accept.sin_addr));
		read_buf[read_size] = '\0';
		printf("receive's char is %s\n",read_buf);
		
		/*****************��������*****************/
		
	}

	close(fd_socket);
	
	exit(0);
	
}