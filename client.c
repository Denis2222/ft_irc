/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/06/07 15:05:52 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>//close
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>//strlen

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define PORT 8067

int main(int ac, char **argv)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct hostent *hostinfo = NULL;
	struct sockaddr_in sin = { 0 }; /* initialise la structure avec des 0 */
	const char *hostname = "localhost";
	char buffer[4096];
	int bufsent;

	bufsent = 0;

	strcat(buffer, "Hello World Socket!");

	hostinfo = gethostbyname(hostname);
	if (hostinfo == NULL) /* l'hôte n'existe pas */
	{
	    fprintf (stderr, "Unknown host %s.\n", hostname);
	    return (1);
	}
	printf("host name:%s", hostinfo->h_name);

	if(sock == INVALID_SOCKET)
	{
	    perror("socket()");
	    return (1);
	}

	sin.sin_addr = *(struct in_addr *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
	sin.sin_port = htons(atoi(argv[1])); /* on utilise htons pour le port */
	sin.sin_family = AF_INET;

	if(connect(sock,(struct sockaddr *) &sin, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
    	perror("connect()");
    	return (1);
	}

	if(send(sock, buffer, strlen(buffer), 0) < 0)
	{
    	perror("send()");
    	return (1);
	}

	while(42)
	{
		
	}

	close(sock);

	return (0);
}
