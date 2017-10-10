/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 02:55:56 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 02:58:54 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int			cmd_out(char *line, t_client *client)
{
	char **cmd;

	if ((ft_strncmp(line, "/help", 5) == 0))
		showmsghelp(client);
	else if ((ft_strncmp(line, "/connect ", 9) == 0) && !client->connect)
	{
		cmd = ft_strsplit(line, ' ');
		if (connect_host(cmd[1], cmd[2], client))
			client->connect = 1;
		ft_tabfree(cmd);
	}
	else if ((ft_strncmp(line, "/disconnect", 11) == 0) && client->connect)
	{
		close(client->socket);
		client->connect = 0;
	}
	else if (ft_strncmp(line, "/quit", 5) == 0)
		client->exit = 0;
	else if (client->connect)
		presend(client, line);
	else
		ft_dprintf(2, "Nothing to do\n");
	return (0);
}

char		*cmd_from_buffer(char *buffer)
{
	int		length;
	int		cmdlength;
	int		pos;
	char	*cmd;
	char	*tmp;

	length = ft_strlen(buffer);
	pos = ft_strlen(ft_strchr(buffer, '\n'));
	cmdlength = length - pos + 1;
	cmd = ft_strsub(buffer, 0, cmdlength - 1);
	tmp = ft_strsub(buffer, cmdlength, length);
	ft_bzero(buffer, BUF_SIZE + 1);
	ft_strcpy(buffer, tmp);
	free(tmp);
	return (cmd);
}

static void	cmd_in_switch(t_client *client, char *cmd)
{
	char	**tab;
	char	*str;

	tab = ft_strsplit(cmd, ' ');
	if (ft_strnstr(cmd, "/nick ", 6))
	{
		ft_strcpy(client->name, tab[1]);
	}
	else if (ft_strnstr(cmd, "/join ", 6))
	{
		str = ft_mprintf("/newmsg [server] Switch to %s channel", tab[1]);
		writemsg(client, str);
		free(str);
		ft_strcpy(client->channel, tab[1]);
	}
	else if (ft_strncmp(cmd, "/newmsg", 7) == 0)
	{
		writemsg(client, cmd);
	}
	ft_tabfree(tab);
}

int			cmd_in(t_client *client)
{
	char *cmd;

	if (ft_strlen(client->buf_read) > 0)
	{
		while (ft_strchr(client->buf_read, '\n'))
		{
			cmd = cmd_from_buffer(client->buf_read);
			if (cmd[0] == '/')
				cmd_in_switch(client, cmd);
			free(cmd);
		}
	}
	return (0);
}
