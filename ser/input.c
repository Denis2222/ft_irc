/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 06:26:59 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/11 01:45:43 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

static void	input_command_nick(t_env *e, int cs, char **tab, char *buffer)
{
	char	*str;

	if (ft_tablen(tab) > 1
		&& tab[1]
		&& ft_strlen(tab[1]) > 2
		&& ft_strlen(tab[1]) < 10)
	{
		if (!search_user(e, tab[1]))
		{
			ft_strcpy(e->fds[cs].name, tab[1]);
			str = ft_mprintf(
				"%s\n/newmsg [%s][server] : Nickname changed to %s\n",
				buffer, e->fds[cs].channel, e->fds[cs].name);
			presend(e, cs, str);
			free(str);
		}
		else
			presend(e, cs, "/newmsg [server] nick already use\n");
	}
	else
		presend(e, cs, "/newmsg [server] Invalid nick name\n");
}

static void	input_command_join(t_env *e, int cs, char **tab, char *buffer)
{
	if (ft_strlen(tab[1]) > 3 && ft_strlen(tab[1]) < 17 && tab[1][0] == '#')
	{
		ft_strcpy(e->fds[cs].channel, tab[1]);
		presend(e, cs, buffer);
		presend(e, cs, "\n");
	}
	else
	{
		presend(e, cs, "/newmsg [server] invalid channel name ( /join [#name]  #name MAX 16 MIN 4)\n");
	}
}

static void	input_command_leave(t_env *e, int cs)
{
	char	*str;

	ft_strcpy(e->fds[cs].channel, GENERAL_CHANNEL);
	str = ft_mprintf("/join %s", GENERAL_CHANNEL);
	presend(e, cs, str);
	free(str);
	presend(e, cs, "\n");
}

void		input_command(t_env *e, int cs, char *buffer)
{
	char	**tab;

	tab = ft_strsplit(buffer, ' ');
	if (ft_strncmp(buffer, "/nick ", 6) == 0)
		input_command_nick(e, cs, tab, buffer);
	if (ft_strncmp(buffer, "/join ", 6) == 0 && ft_tablen(tab) > 1 &&
		tab[1] && ft_strlen(tab[1]))
		input_command_join(e, cs, tab, buffer);
	if (ft_strncmp(buffer, "/leave", 6) == 0)
		input_command_leave(e, cs);
	if (ft_strncmp(buffer, "/msg", 2) == 0 && ft_tablen(tab) > 2
		&& tab[1] && ft_strlen(tab[1]))
		private_message(e, cs, buffer);
	if (ft_strncmp(buffer, "/who", 2) == 0)
		who_list(e, cs);
	ft_tabfree(tab);
}

void		input(t_env *e, int cs, char *buffer)
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
