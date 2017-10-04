/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 06:27:42 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 08:51:53 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "bircd.h"

void	check_fd(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->r > 0))
	{
		if (FD_ISSET(i, &e->fd_read))
		{
			printf("FD_ISSET(%d, fd_read)\n", i);
			e->fds[i].fct_read(e, i);
		}
		if (FD_ISSET(i, &e->fd_write))
		{
			printf("FD_ISSET(%d, fd_write)\n", i);
			e->fds[i].fct_write(e, i);
		}
		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->r--;
		i++;
	}
}
