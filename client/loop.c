/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/02 16:10:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int loop_connect(fd_set *rdfs, t_client *client)
{
	char buffer[BUF_SIZE];
	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(client->socket, rdfs);
	ft_printf("#[%s][%s]: ", client->channel, client->name);

	if (select(client->socket + 1, rdfs, NULL, NULL, NULL) == -1)
	{
	   dprintf(STDERR_FILENO, "select() error");
	   return (1);
	}
	if (FD_ISSET(STDIN_FILENO, rdfs))
	{
		char	*line;
		get_next_line_single(STDIN_FILENO, &line);
		ft_strcpy(buffer, line);
		cmd_out(buffer, client);
		free(line);
		line = NULL;
	}

	if (FD_ISSET(client->socket, rdfs))
	{
		int n = read_server(client->socket, buffer);
		if (n == 0)
		{
		   ft_printf("server disconnected");
		   return (0);
	   }
	   cmd_in(client, buffer);
   }
   return (1);
}

int loop_disconnect(t_client *client)
{
	char	*line;
	char buffer[BUF_SIZE];

	get_next_line_single(STDIN_FILENO, &line);
	ft_strcpy(buffer, line);
	cmd_out(buffer, client);
	free(line);
	line = NULL;
	return (1);
}
