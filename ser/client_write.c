/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 04:08:00 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 06:58:21 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "bircd.h"

void	client_write(t_env *e, int cs)
{
	char	tmp[BUF_SIZE + 1];
	int		res;

	res = send(cs, e->fds[cs].buf_write, SPEED_MAX, 0);
	if (res > 0)
	{
		ft_strcpy(tmp, &e->fds[cs].buf_write[res]);
		ft_bzero(e->fds[cs].buf_write, BUF_SIZE + 1);
		ft_strcpy(e->fds[cs].buf_write, tmp);
	}
	if (res == 0)
	{
		ft_printf("Client %d disconnect", cs);
		clean_fd(&e->fds[cs]);
	}
	return ;
}
