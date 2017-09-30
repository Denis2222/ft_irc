/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/09/30 22:17:51 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int read_server(int sock, char *buffer)
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

static void send_server(int sock, char *cmd)
{
	ft_printf("Send %d, %s", ft_strlen(cmd), cmd);
   	if(send(sock, cmd, strlen(cmd), 0) < 0)
   	{
    	perror("send()");
    	//exit(1);
   	}
}

static void write_server(int sock, const char *buffer)
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

int main(int ac, char **argv)
{
	t_client client;

	if (checkhost(&client) == 1)
		return (EXIT_FAILURE);
	if (checksocket(&client) == 1)
		return (EXIT_FAILURE);
	if (connectsocket(&client, argv[1]) == 1)
		return (EXIT_FAILURE);

	char buffer[BUF_SIZE];
	fd_set	rdfs;

	while(42)
	{
		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);
		FD_SET(client.socket, &rdfs);
		ft_printf("#:");

		if (select(client.socket + 1, &rdfs, NULL, NULL, NULL) == -1)
		{
			dprintf(STDERR_FILENO, "select() error");
			return (1);
		}

		if (FD_ISSET(STDIN_FILENO, &rdfs))
		{
			char	*line;

			get_next_line(0, &line);

			ft_printf("CMD:%s\n", line);
			ft_strcpy(buffer, line);

			write_server(client.socket, line);
			//buffer[0] = 0;
			//line = NULL;
			//free(line);
		}
		else if (FD_ISSET(client.socket, &rdfs))
		{
			int n = read_server(client.socket, buffer);
			if (n == 0)
			{
				ft_printf("server disconnected");
				break;
			}
			ft_printf("#{green}%s{eoc}\n", buffer);
		}
	}
	close(client.socket);
	return (0);
}
