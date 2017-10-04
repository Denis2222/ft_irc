/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 06:26:59 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 15:14:00 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void input_message(t_env *e, int cs, char *buffer, size_t r)
{
	int	i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)	//Send to all other
		{
			if (1 || (i != cs)) // Not him
			{
				//ft_printf("Send To %d %s %s", ft_strcmp(e->fds[i].channel, e->fds[cs].channel),e->fds[cs].channel, e->fds[i].channel );
				if (ft_strcmp(e->fds[i].channel, e->fds[cs].channel) == 0) // Only same channel
				{
					//ft_printf("Send good ");
					char *msg;

					//ft_printf("{red}DEBUG:%s %d{eoc}\n", buffer, ft_strlen(buffer));
					msg = ft_mprintf("/newmsg [%s][%s]:%s", e->fds[cs].channel, e->fds[cs].name, buffer);

					//send(i, msg, ft_strlen(msg), 0);
					ft_printf("->%s\n", msg);
					write_client(i, msg);
					free(msg);
					printf("send to [%d]\n", i);
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

	tmp = ft_mprintf("/newmsg [%s][server]User in channel: %s", e->fds[cs].channel, str);
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

int private_message(t_env *e, int cs, char *buffer, size_t r)
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
		send = ft_mprintf("/newmsg [private][%s]:[%s]:%s", e->fds[cs].name, nick, texte);
		write_client(i, send);
		free(send);

		send = ft_mprintf("/newmsg [private][%s]:[%s]:%s", e->fds[cs].name, nick, texte);
		write_client(cs, send);
		free(send);
		ft_printf("Send to : %s -> %s", nick, send);
		return (0);
	}
	ft_tabfree(tab);
	return (1);
}

void input_command(t_env *e, int cs, char *buffer, size_t r)
{
	char **tab;
	char  *str;

	ft_printf("CMD:%s %s %s\n", e->fds[cs].channel, e->fds[cs].name, buffer);
	tab = ft_strsplit(buffer, ' ');
	if (ft_strnstr(buffer, "/nick ", 6))
	{
		ft_strcpy(e->fds[cs].name, tab[1]);

		str = ft_mprintf("%s\n/newmsg [%s][server] : Nickname changed to %s", buffer,e->fds[cs].channel, e->fds[cs].name);
		write_client(cs, str);
		free(str);
	}
	if (ft_strnstr(buffer, "/join ", 6))
	{
		ft_strcpy(e->fds[cs].channel, tab[1]);
		write_client(cs, buffer);

	}

	if (ft_strncmp(buffer, "/msg", 2) == 0)
	{
		private_message(e, cs, buffer, r);
	}

	if (ft_strncmp(buffer, "/who", 2) == 0)
	{
		ft_printf("Detected");
		str = who_list(e, cs);
		write_client(cs, str);
		free(str);
	}

	ft_tabfree(tab);
}

void input(t_env *e, int cs, char *buffer, size_t r)
{
	if (buffer[0] == '/')
	{
		input_command(e, cs, buffer, r);
	}
	else
	{
		input_message(e, cs, buffer, r);
	}
	free(buffer);
}
