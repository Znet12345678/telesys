/*
*Copyright (c) Zachary James Schlotman 2015
*Do not redistribute without writen consent of author
*Do not modify code without writen consent of author
*Do not decompile
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/time.h>
#define TRUE 1
#define FALSE 0
int main(int a, char *b[])
{
	if (a != 3)
	{
		printf("Syntax: ${server_exec} Path_to_program socket #\n");
	}
	else
	{
		//printf("%s",b[1]);
		int es_socket;
		int new_socket;
		int client_socket[atoi(b[2])];
		for (int i = 0; i < atoi(b[2]);i++)
		{
			client_socket[i] = 0;
		}
		struct sockaddr_in address;
		const char *buffer = cat(b[1]);
		printf("Establishing socket\n");
		es_socket = socket(AF_INET,SOCK_STREAM,0);
		int opt = TRUE;
		if(es_socket == 0)
		{
			perror("Creating socket\n");
			exit(EXIT_FAILURE);
		}
		setsockopt(es_socket,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,sizeof(opt));
		address.sin_family = AF_INET;
		address.sin_port = htons(2718);
		address.sin_addr.s_addr = INADDR_ANY;
		printf("Binding port\n");
		bind(es_socket,(struct sockaddr*)&address,sizeof(address));
		int addrlen = sizeof(address);
		printf("Listining\n");
		listen(es_socket,atoi(b[2]));
		fd_set rfds;
		int activity;
		while (TRUE)
		{
			FD_ZERO(&rfds);
			FD_SET(es_socket,&rfds);
			for (int i = 0; i < atoi(b[2]);i++)
			{
				if(client_socket[i] > 0)
				{
					FD_SET(es_socket,&rfds);
				}
			}
			activity = select(atoi(b[2]) + 3,&rfds,NULL,NULL,NULL);
			if (FD_ISSET(es_socket,&rfds))
			{
				printf("Accepting\n");
				new_socket = accept(es_socket,(struct sockaddr *)&address,&addrlen);
				send(new_socket,buffer,strlen(buffer),0);
				for (int i = 0; i < atoi(b[2]);i++)
				{
					if(client_socket[i] == 0)
					{
						client_socket[i] = new_socket;
						i = atoi(b[2]);
					}
				}
				close(new_socket);
				for (int i = 0; i < atoi(b[2]);i++)
				{
					close(client_socket[i]);
				}
			}
		}
	}
}
