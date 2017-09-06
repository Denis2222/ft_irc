/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/09/06 07:27:52 by dmoureu-         ###   ########.fr       */
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

static void write_server(int sock, const char *buffer)
{
	int size;

	size = ft_strlen(buffer);
	//while (size > 0)
	//ft_printf("size of buffer: %d size int :%d", ft_strlen(buffer), sizeof(unsigned int));
   	if(send(sock, buffer, strlen(buffer), 0) < 0)
   	{
    	perror("send()");
    	exit(1);
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

			//if (0)
				write_server(client.socket, buffer);
			buffer[0] = 0;
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
			ft_printf("buffer incoming %s", buffer);
		}
	}
	close(client.socket);
	return (0);
}
