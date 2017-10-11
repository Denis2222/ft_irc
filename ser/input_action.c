/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 06:47:34 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/11 02:31:33 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	input_message(t_env *e, int cs, char *buffer)
{
	int		i;
	char	*msg;
	char	*full;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT)
		{
			if (ft_strcmp(e->fds[i].channel, e->fds[cs].channel) == 0)
			{
				msg = ft_mprintf("/newmsg [%s][%s]:",
					e->fds[cs].channel, e->fds[cs].name);
				full = ft_strjoin(msg, buffer);
				free(msg);
				msg = ft_strjoin(full, "\n");
				presend(e, i, msg);
				free(msg);
				free(full);
			}
		}
		i++;
	}
}

void	who_list(t_env *e, int cs)
{
	char	*str;
	char	*tmp;
	int		i;

	str = ft_strdup(" ");
	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT
			&& ft_strcmp(e->fds[i].channel, e->fds[cs].channel) == 0)
		{
			tmp = ft_mprintf("%s %s", str, e->fds[i].name);
			free(str);
			str = tmp;
		}
		i++;
	}
	tmp = ft_mprintf("/newmsg [%s][server]User in channel: %s\n",
		e->fds[cs].channel, str);
	free(str);
	presend(e, cs, tmp);
	free(tmp);
}

int		search_user(t_env *e, char *nick)
{
	int	i;

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

int		private_message(t_env *e, int cs, char *buffer)
{
	char	**tab;
	char	*nick;
	char	*texte;
	char	*send;
	int		i;

	tab = ft_strsplit(buffer, ' ');
	if (ft_tablen(tab) < 3)
		return (1);
	nick = tab[1];
	if ((i = search_user(e, nick)) > 0)
	{
		texte = ft_strstr(buffer, nick) + ft_strlen(nick);
		send = ft_mprintf("/newmsg [private][%s]:[%s]:%s\n",
			e->fds[cs].name, nick, texte);
		presend(e, i, send);
		free(send);
		send = ft_mprintf("/newmsg [private][%s]:[%s]:%s\n",
			e->fds[cs].name, nick, texte);
		presend(e, cs, send);
		return (0);
	}
	ft_tabfree(tab);
	return (1);
}
