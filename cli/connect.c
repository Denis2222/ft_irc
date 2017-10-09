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

void tryconnect(t_client *client, int ac, char **argv)
{
	if (ac == 2)
		if (connect_host(argv[1], "2000", client))
			client->connect = 1;
	if (ac == 3)
		if (connect_host(argv[1], argv[2], client))
			client->connect = 1;
}

int connect_host(char *host, char *port, t_client *client)
{
	(void)host;
	if (checkhost(client, host) == 1)
		return (0);
	if (checksocket(client) == 1)
		return (0);
	if (connectsocket(client, port) == 1)
		return (0);
	return (1);
}

int checkhost(t_client *client, char *hostname)
{
	struct hostent	*hostinfo = NULL;

	hostinfo = gethostbyname(hostname);
	if (hostinfo == NULL) /* l'hôte n'existe pas */
	{
		writemsg(client, "        Unknown host\n");
	    ft_printf ("Unknown host %s.\n", hostname);
	    return (1);
	}
	client->hostinfo = hostinfo;
	return (0);
}

int checksocket (t_client *client)
{
	client->socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client->socket == INVALID_SOCKET)
	{
	    ft_printf ("socket error \n");
	    return (1);
	}
	return (0);
}

int connectsocket(t_client *client, char *port)
{
	if (port == NULL || ft_atoi(port) <= 0)
	{
		writemsg(client, "        Invalid port number");
		ft_printf("Invalid port number");
		return (1);
	}
	ft_bzero(&(client->sin), sizeof(struct sockaddr_in));
	client->sin.sin_addr = *(struct in_addr *) client->hostinfo->h_addr;
	client->sin.sin_port = htons(ft_atoi(port));
	client->sin.sin_family = AF_INET;
	if(connect(client->socket,(struct sockaddr *) &client->sin, sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
    	writemsg(client, "        Connection fail : Check host and port !\n");
    	return (1);
	}
	writemsg(client, "        Connection established !");
	ft_printf("Connection established !\n");
	return (0);
}
