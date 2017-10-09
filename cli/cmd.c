/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 18:06:16 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int cmd_out(char *line, t_client *client)
{
   char **cmd;

   if (ft_strnstr(line, "/connect ", 9))
   {
	  cmd = ft_strsplit(line, ' ');
	  ft_printf("connect to : %s ...\n", cmd[1]);
	  ft_printf("HERE?");
	  if (connect_host(cmd[1], cmd[2], client))
		client->connect = 1;
   } else {
		if (client->connect) {
			presend(client, line);
		}
   }
   return (0);
}

char *cmd_from_buffer(char *buffer)
{
	int length;
	int cmdlength;
	int pos;
	char *cmd;

	char *tmp;
	length = ft_strlen(buffer);
	pos = ft_strlen(ft_strchr(buffer, '\n'));
	cmdlength = length - pos+1;
	
	cmd = ft_strsub(buffer, 0, cmdlength - 1);
	tmp = ft_strsub(buffer, cmdlength, length);
	ft_bzero(buffer, BUF_SIZE + 1);
	ft_strcpy(buffer, tmp);
	free(tmp);
	return (cmd);
}

int cmd_in(t_client *client)
{
	char **tab;
	char *cmd;

	if (ft_strlen(client->buf_read) > 0)
	{
		while (ft_strchr(client->buf_read, '\n'))
		{
			dprintf(2, " return detect go \n");
			cmd = cmd_from_buffer(client->buf_read);
			dprintf(2, " cmd exrtract from buffer |%s| \n", cmd);
			if (cmd[0] == '/') {
				tab = ft_strsplit(cmd, ' ');
				if (ft_strnstr(cmd, "/nick ", 6))
				{
					ft_strcpy(client->name, tab[1]);
					ft_printf("Change name");
				}
				if (ft_strnstr(cmd, "/join ", 6))
				{
					ft_printf("Change channel");
					ft_strcpy(client->channel, tab[1]);
				}
				if (ft_strncmp(cmd, "/newmsg", 7) == 0)
				{
					ft_dprintf(2, "\nNEW MESSAGE  %s\n", &cmd[7]);
					client->msg = addmsg(&client->msg, newmsg(&cmd[7], client));
				}
				ft_tabfree(tab);
			}
			free(cmd);
		}
	}
	return (0);
}
