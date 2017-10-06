/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:42:07 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 17:46:48 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

#define MAX_CMD_SIZE 512

void	client_read(t_env *e, int cs)
{
	int	res;
	int head;

	head = ft_strlen(e->fds[cs].buf_read);
	if (head >= BUF_SIZE-SPEED_MAX)
	{
		ft_printf("BUFFER FULL");
		return ;
	}
	res = recv(cs, &e->fds[cs].buf_read[head], SPEED_MAX, 0);
	if (res == 0)
	{
		ft_printf("Client %d disconnect", cs);
		clean_fd(&e->fds[cs], cs);
	}
	if (res > 0)
	{
		e->fds[cs].buf_read[head+res] = 0;
	}
}