/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 06:26:59 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 18:01:27 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void input_message(t_env *e, int cs, char *buffer)
{
	int	i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)	//Send to all other
		{
			if (1 || (i != cs)) // Not him
			{
				if (ft_strcmp(e->fds[i].channel, e->fds[cs].channel) == 0) // Only same channel
				{
					char *msg;
					char *full;

					msg = ft_mprintf("/newmsg [%s][%s]:", e->fds[cs].channel, e->fds[cs].name);
					full = ft_strjoin(msg, buffer);
					free(msg);
					//asprintf(&msg, "/newmsg [%s][%s]:%s\n", e->fds[cs].channel, e->fds[cs].name, buffer);
					msg = ft_strjoin(full, "\n");
					presend(e, i, msg);
					free(msg);
					free(full);
				}
			}
		}
		i++;
	}
}

char *who_list(t_env *e, int cs)
{
	char *str;
	char *tmp;
	int i;

	str = ft_strdup(" ");
	i = 0;
	while (i < e->maxfd)
	{
		if (ft_strcmp(e->fds[i].channel, e->fds[cs].channel) == 0)
		{
			tmp = ft_mprintf("%s %s", str, e->fds[i].name);
			free(str);
			str = tmp;
		}
		i++;
	}

	tmp = ft_mprintf("/newmsg [%s][server]User in channel: %s\n", e->fds[cs].channel, str);
	free(str);
	return (tmp);
}

int search_user(t_env *e, char *nick)
{
	int i;

	i = 0;
	while (i < e->maxfd)
	{
		if (ft_strcmp(e->fds[i].name, nick) == 0)
		{
			return (i);
		}
		i++;
	}
	return (0);
}

int private_message(t_env *e, int cs, char *buffer)
{
	char **tab;
	char *nick;
	char *texte;
	char *send;
	int  i;

	tab = ft_strsplit(buffer, ' ');
	if (ft_tablen(tab) < 3)
	{
		return (1);
	}
 	nick = tab[1];
	if ((i = search_user(e, nick)) > 0)
	{
		texte = ft_strstr(buffer, nick) + ft_strlen(nick);
		send = ft_mprintf("/newmsg [private][%s]:[%s]:%s\n", e->fds[cs].name, nick, texte);
		presend(e, i, send);
		free(send);

		send = ft_mprintf("/newmsg [private][%s]:[%s]:%s\n", e->fds[cs].name, nick, texte);
		presend(e, cs, send);
		return (0);
	}
	ft_tabfree(tab);
	return (1);
}

void input_command(t_env *e, int cs, char *buffer)
{
	char **tab;
	char  *str;

	tab = ft_strsplit(buffer, ' ');
	if (ft_strncmp(buffer, "/nick ", 6) == 0)
	{
		if (ft_tablen(tab) > 1 && tab[1] && ft_strlen(tab[1]) > 2 && ft_strlen(tab[1]) < 10) 
		{
			if (!search_user(e, tab[1]))
			{
				ft_strcpy(e->fds[cs].name, tab[1]);
				str = ft_mprintf("%s\n/newmsg [%s][server] : Nickname changed to %s\n", buffer,e->fds[cs].channel, e->fds[cs].name);
				presend(e, cs, str);
				free(str);
			}
			else
			{
				ft_strcpy(e->fds[cs].channel, GENERAL_CHANNEL);
				str = ft_mprintf("/newmsg [server] nick already use");
				presend(e, cs, str);
				free(str);
				presend(e, cs, "\n");
			}
		}
		else
		{
			ft_strcpy(e->fds[cs].channel, GENERAL_CHANNEL);
			str = ft_mprintf("/newmsg [server] Invalid nick name");
			presend(e, cs, str);
			free(str);
			presend(e, cs, "\n");
		}
	}
	if (ft_strncmp(buffer, "/join ", 6) ==0 && ft_tablen(tab) > 1 && tab[1] && ft_strlen(tab[1]))
	{
		ft_strcpy(e->fds[cs].channel, tab[1]);
		presend(e, cs, buffer);
		presend(e, cs, "\n");

	}

	if (ft_strncmp(buffer, "/leave", 6) == 0)
	{
		ft_strcpy(e->fds[cs].channel, GENERAL_CHANNEL);
		str = ft_mprintf("/join %s", GENERAL_CHANNEL);
		presend(e, cs, str);
		free(str);
		presend(e, cs, "\n");
	}

	if (ft_strncmp(buffer, "/msg", 2) == 0 && ft_tablen(tab) > 2 && tab[1] && tab[1] && ft_strlen(tab[1]))
	{
		private_message(e, cs, buffer);
	}

	if (ft_strncmp(buffer, "/who", 2) == 0)
	{
		ft_printf("Detected");
		str = who_list(e, cs);
		presend(e, cs, str);
		presend(e, cs, "\n");
		free(str);
	}

	ft_tabfree(tab);
}

void input(t_env *e, int cs, char *buffer)
{
	if (buffer[0] == '/')
	{
		input_command(e, cs, buffer);
	}
	else
	{
		input_message(e, cs, buffer);
	}
}
