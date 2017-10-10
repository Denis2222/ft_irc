/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 03:08:05 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	events(t_client *client)
{
	char	ln[PROMPT_SIZE_MAX];
	int		len;
	char	*line;

	if (NCURSE)
	{
		len = get_line_non_blocking(&client->lnbuffer, ln, sizeof(ln));
		if (len > 0 && ft_strlen(ln))
		{
			cmd_out(ln, client);
			ft_bzero(ln, PROMPT_SIZE_MAX);
		}
		view(client);
		refresh();
	}
	else
	{
		get_next_line_single(STDIN_FILENO, &line);
		cmd_out(line, client);
		free(line);
		line = NULL;
	}
}

static int	initfd(t_client *client)
{
	FD_ZERO(&client->fd_read);
	FD_ZERO(&client->fd_write);
	FD_SET(STDIN_FILENO, &client->fd_read);
	if (client->connect)
	{
		FD_SET(client->socket, &client->fd_read);
		if (ft_strlen(client->buf_write))
			FD_SET(client->socket, &client->fd_write);
	}
	if (select(client->socket + 1, &client->fd_read, &client->fd_write,
		NULL, NULL) == -1)
		return (1);
	return (0);
}

static int	checkfd(t_client *client)
{
	if (FD_ISSET(STDIN_FILENO, &client->fd_read))
	{
		events(client);
		view(client);
	}
	if (client->connect)
	{
		if (FD_ISSET(client->socket, &client->fd_read))
		{
			if (read_server(client) == 0)
			{
				writemsg(client, "Disconnected\n");
				client->connect = 0;
			}
			cmd_in(client);
			refresh();
			view(client);
		}
		if (FD_ISSET(client->socket, &client->fd_write))
			server_write(client);
	}
	return (client->exit);
}

int			loop(t_client *client)
{
	initfd(client);
	return (checkfd(client));
}
