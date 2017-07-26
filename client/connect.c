/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 07:47:04 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/07/26 09:10:59 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int checkhost(t_client *client)
{
	const char		*hostname = "localhost";
	struct hostent	*hostinfo = NULL;

	hostinfo = gethostbyname(hostname);
	if (hostinfo == NULL) /* l'hôte n'existe pas */
	{
	    dprintf (STDERR_FILENO, "Unknown host %s.\n", hostname);
	    return (1);
	}
	ft_printf("host name:%s", hostinfo->h_name);
	client->hostinfo = hostinfo;
	return (0);
}

int checksocket (t_client *client)
{
	client->socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client->socket == INVALID_SOCKET)
	{
	    dprintf (STDERR_FILENO, "socket error \n");
	    return (1);
	}
	return (0);
}

int connectsocket(t_client *client, char *port)
{
	if (port == NULL || atoi(port) <= 0)
	{
		dprintf(STDERR_FILENO, "Invalid port number");
		return (1);
	}
	bzero(&(client->sin), sizeof(struct sockaddr_in)); /* initialise la structure avec des 0 */
	client->sin.sin_addr = *(struct in_addr *) client->hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
	client->sin.sin_port = htons(atoi(port)); /* on utilise htons pour le port */
	client->sin.sin_family = AF_INET;
	if(connect(client->socket,(struct sockaddr *) &client->sin, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
    	perror("connect()");
    	return (1);
	}
	return (0);
}
