#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define TCP_port 3333

void main()
{
	int fd_socket = 0;
	int ret = 0;
	/******定义TCP*****/
	
	in_addr_t TCP_addr = 0;
	struct sockaddr_in  TCP_stuct;
	char *TCP_addrs = NULL;
	ssize_t send_buf = 0;
	
	system("rm *.bak");
	

	
	/*******创建IPV4 TCP套接字******/ 
	
		/********转换地址***********/

	
	fd_socket = socket(AF_INET,SOCK_STREAM ,0);
	printf("socket's fd_socket is %d\n",fd_socket);
	
	
	/***************连接******************/
	bzero(&TCP_stuct,sizeof(struct sockaddr));
	
	TCP_stuct.sin_port = htons(TCP_port);
	
	TCP_addr = inet_addr("192.168.0.105");
	printf("addr is  %d\n",TCP_addr);
	TCP_stuct.sin_addr.s_addr = TCP_addr;
	TCP_addrs = inet_ntoa(TCP_stuct.sin_addr);
	printf("ip is %s\n",TCP_addrs);
	
	TCP_stuct.sin_family = AF_INET;
	ret = connect(fd_socket,(struct sockaddr *)(&TCP_stuct),sizeof(struct sockaddr));
	printf("connect's ret is %d\n",ret);
	if(ret == -1)
		{
			exit(0);
		}
	
	send_buf = send(fd_socket,"yixi-sha",8,0);
	printf("send_buf is %d\n",send_buf);
		
	close(fd_socket);
	
	exit(0);
	
}