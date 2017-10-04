/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 15:53:40 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void events(t_client *client)
{
	char ln[PROMPT_SIZE_MAX];
	int len = 0;

	len = get_line_non_blocking(&client->lnbuffer, ln, sizeof(ln));
	if(len > 0) {
		if(strcmp(ln, "exit") == 0) {
			//break;
			ft_printf("Exit ask");
		}
		cmd_out(ln, client);
	}
	clear();
	view(client);
}

int loop_connect(fd_set *rdfs, t_client *client)
{
	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(client->socket, rdfs);
	if (select(client->socket + 1, rdfs, NULL, NULL, NULL) == -1)
	{
		//dprintf(STDERR_FILENO, "select resize");
		//perror("select()");
		//clear();
		return (1);
	}
	if (FD_ISSET(STDIN_FILENO, rdfs))
	{
		clear();
		events(client);
	}

	if (FD_ISSET(client->socket, rdfs))
	{
	   cmd_in(client);
	   events(client);
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
