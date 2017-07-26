/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/07/26 09:32:03 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int read_server(int sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, 4096 - 1, 0)) < 0)
   {
      perror("recv()");
      exit(1);
   }

   buffer[n] = 0;

   return n;
}

static void write_server(int sock, const char *buffer)
{
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

	char buffer[4096];
	fd_set	rdfs;

	while(42)
	{
		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);
		FD_SET(client.socket, &rdfs);

		if (select(client.socket + 1, &rdfs, NULL, NULL, NULL) == -1)
		{
			dprintf(STDERR_FILENO, "select() error");
			return (1);
		}

		if (FD_ISSET(STDIN_FILENO, &rdfs))
		{
			char	*line;
			ft_printf("In keyboard deteted");
			if (!get_next_line(0, &line))
			{
				ft_printf("\n");
				exit(EXIT_SUCCESS);
			}
			ft_printf("GNL END %s", line);
			ft_strcpy(buffer, line);

			write_server(client.socket, buffer);

			line = NULL;
			free(line);
		} else if (FD_ISSET(client.socket, &rdfs)) {
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
