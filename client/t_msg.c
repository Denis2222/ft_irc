/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_msg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymou <anonymou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 18:36:48 by anonymou          #+#    #+#             */
/*   Updated: 2017/10/02 20:38:15 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_msg	*newmsg(char *text)
{
	t_msg	*msg;

	msg = (t_msg *)malloc(sizeof(t_msg));
	msg->text = ft_strdup(text);
	msg->next = NULL;
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
		//ft_printf("%p %p ", current, current->next);
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
