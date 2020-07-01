#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int tcp_socket_init(unsigned short port, const char *ip_address)
{
	int sockfd = -1; 
	struct sockaddr_in my_addr; 

	printf("TCP Server Started at port %d!\n", port);
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	if(sockfd < 0){
		perror("socket error");
		return -1;
	}

	bzero(&my_addr, sizeof(my_addr)); 
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = htonl(inet_addr(ip_address));

	return sockfd;
}

int tcp_socket_send(int tcp_socket, const char *tcp_data)
{
	int res = -1;

	if (-1 == tcp_socket)
		return -1;

	res = send(tcp_socket,tcp_data,sizeof(tcp_data),0);/*use sizeof to check the count*/
	if (-1 == res)
		return -1;

	return res;
}

int tcp_socket_receive(int tcp_socket, char *tcp_data)
{
	int res = 1;
	
	if(-1 == tcp_socket)
		return -1;
	
	res = recv(tcp_socket,tcp_data,sizeof(tcp_data),0); 
	if(-1 == res)
		return -1;
	
	return res;
}