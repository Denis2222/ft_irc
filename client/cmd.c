/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/02 16:05:37 by anonymous        ###   ########.fr       */
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
			write_server(client->socket, line);
		}
   }
   return (0);
}

int cmd_in(t_client *client, char *cmd)
{
	//ft_printf("|{green}%s{eoc}|\n", cmd);
	char **tab;
	char **cmds;
	int i;

	i = 0;
	cmds = ft_strsplit(cmd, '\n');
	while (cmds[i] != '\0')
	{
		if (cmds[i][0] == '/') {
			tab = ft_strsplit(cmds[i], ' ');
			if (ft_strnstr(cmds[i], "/nick ", 6))
			{
				ft_strcpy(client->name, tab[1]);
			}
			if (ft_strnstr(cmds[i], "/channel ", 9))
			{
				ft_strcpy(client->channel, tab[1]);
			}
			if (ft_strnstr(cmds[i], "/newmsg ", 8))
			{
				ft_printf("\n%s\n", &cmd[8]);
			}
			ft_tabfree(tab);
		}
		i++;
	}
	ft_tabfree(cmds);
}
