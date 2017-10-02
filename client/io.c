/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/02 15:46:55 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int read_server(int sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      exit(1);
   }

   buffer[n] = 0;

   return n;
}

void send_server(int sock, char *cmd)
{
	//ft_printf("Send %d, %s", ft_strlen(cmd), cmd);
   	if(send(sock, cmd, strlen(cmd), 0) < 0)
   	{
    	perror("send()");
    	//exit(1);
   	}
}

void write_server(int sock, const char *buffer)
{
	int offset;
	int allsend;
	char *packet;

	allsend = 0;
	offset = 0;
	//ft_printf("size of buffer: %d size int :%d", ft_strlen(buffer), sizeof(unsigned int));

	if (ft_strlen(buffer) > BUF_SIZE)
	{
		while (allsend == 0) {
			packet = ft_strsub(buffer, offset, BUF_SIZE);
			send_server(sock, (char *)packet);
			if (ft_strlen(packet) < BUF_SIZE)
			{
				allsend = 1;
			} else {
				offset += BUF_SIZE;
			}
			free(packet);
		}
	} else {
		send_server(sock, (char *)buffer);
	}
}
