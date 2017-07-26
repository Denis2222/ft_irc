/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 07:48:58 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/07/26 08:21:36 by dmoureu-         ###   ########.fr       */
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
#include <libft.h>


#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define PORT 8067

typedef struct		s_client
{
	struct hostent	*hostinfo;
	int				socket;
	struct sockaddr_in sin;
}					t_client;

int checkhost(t_client *client);
int checksocket (t_client *client);
int connectsocket(t_client *client, char *port);
