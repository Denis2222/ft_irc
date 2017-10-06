/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_msg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymou <anonymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 18:36:48 by anonymou          #+#    #+#             */
/*   Updated: 2017/10/04 12:50:37 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_msg	*newmsg(char *text, t_client *client)
{
	t_msg	*msg;
	char **tab;

	msg = (t_msg *)malloc(sizeof(t_msg));
	msg->text = ft_strdup(text);
	msg->next = NULL;
	msg->color = 1;
	tab = ft_strsplit(text, ':');
	if (tab != NULL && ft_tablen(tab) > 0)
	{
		if (ft_strstr(tab[0], client->name))
			msg->color = 2;
		else if (ft_strstr(tab[0], "server"))
			msg->color = 3;
		ft_tabfree(tab);
	}

	return (msg);
}

t_msg	*addmsg(t_msg **lstmsg, t_msg *msg)
{
	t_msg	*beginlst;
	t_msg	*current;

	beginlst = *lstmsg;
	current = beginlst;
	if (!*lstmsg)
		beginlst = msg;
	else
	{
		while (current->next)
			current = current->next;
		current->next = msg;
	}
	return (beginlst);
}

int		lenmsg(t_msg *msg)
{
	int		length;
	t_msg	*mmsg;

	mmsg = msg;
	length = 0;
	while (mmsg)
	{
		length++;
		mmsg = mmsg->next;
	}
	return (length);
}
