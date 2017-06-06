/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/06/06 20:21:57 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>//close
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>//strlen

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define PORT 8067

int main(void)
{

	struct sockaddr_in sin = { 0 }; /* initialise la structure avec des 0 */
	struct sockaddr_in csin = { 0 }; /* initialise la structure avec des 0 */

	char buffer[4096];
	strcat(buffer, "Hello World Socket!");

	int bufsent;
	bufsent = 0;
	unsigned int sinsize = sizeof csin;

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET)
	{
	    perror("socket()");
	    return (1);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(PORT); /* on utilise htons pour le port */
	sin.sin_family = AF_INET;

	if(bind(sock,(struct sockaddr *) &sin, sizeof(sin)) == SOCKET_ERROR)
	{
    	perror("bind() fails");
    	return (1);
	}

	if(listen(sock, 5) == SOCKET_ERROR)
	{
	    perror("listen()");
	    return (1);
	}

	int csock = accept(sock, (struct sockaddr *)&csin, &sinsize);
	if(csock == INVALID_SOCKET)
	{
    	perror("accept()");
    	return (1);
	}

	int n = 0;

	if((n = recv(csock, buffer, sizeof buffer - 1, 0)) < 0)
	{
	    perror("recv()");
	    return (1);
	}
	buffer[n] = '\0';

	printf(" recu : %s", buffer);

	close(sock);
	close(csock);
	return (0);
}
