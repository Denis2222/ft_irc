/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:42:07 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 06:57:59 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

static void	client_read_ok(t_env *e, int cs, int head, int res)
{
	e->fds[cs].buf_read[head + res] = 0;
	if (!ft_streachr(e->fds[cs].buf_read, ft_isprint))
	{
		bzero(e->fds[cs].buf_read, BUF_SIZE);
		ft_printf("Client %d eject for spam non ascii haxx !", cs);
		clean_fd(&e->fds[cs]);
		close(cs);
	}
}

void		client_read(t_env *e, int cs)
{
	int	res;
	int head;

	head = ft_strlen(e->fds[cs].buf_read);
	if (head >= MAX_CMD_SIZE)
	{
		ft_printf("MAX_CMD_SIZE");
		clean_fd(&e->fds[cs]);
		close(cs);
		return ;
	}
	res = recv(cs, &e->fds[cs].buf_read[head], SPEED_MAX, 0);
	if (res == 0)
	{
		ft_printf("Client %d disconnect", cs);
		clean_fd(&e->fds[cs]);
		close(cs);
	}
	if (res > 0)
	{
		client_read_ok(e, cs, head, res);
	}
}
