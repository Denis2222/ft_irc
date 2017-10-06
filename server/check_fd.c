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

char *cmd_from_buffer(char *buffer)
{
	int length;
	int cmdlength;
	int pos;
	char *cmd;

	char *tmp;
	length = ft_strlen(buffer);
	pos = ft_strlen(ft_strchr(buffer, '\n'));
	cmdlength = length - pos;

	cmd = ft_strsub(buffer, 0, cmdlength);
	tmp = ft_strsub(buffer, cmdlength+1, length);


	ft_printf("Yatao : cmd[%s] tmp[%s]", cmd, tmp);
	bzero(buffer, BUF_SIZE + 1);
	ft_strcpy(buffer, tmp);
	free(tmp);
	return (cmd);
}

void	check_fd(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->r > 0))
	{
		if (FD_ISSET(i, &e->fd_read) && e->fds[i].fct_read != NULL)
		{
			//printf("FD_ISSET(%d, fd_read)\n", i);
			if (i < 100)
				e->fds[i].fct_read(e, i);
			else
				{
					ft_printf("bug crame");
					exit(1);
				}
		}
		if (FD_ISSET(i, &e->fd_write) && e->fds[i].fct_write != NULL)
		{
			//printf("FD_ISSET(%d, fd_write)\n", i);
			e->fds[i].fct_write(e, i);
		}
		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->r--;

		if (ft_strlen(e->fds[i].buf_read) > 0) //Quelque chose disponible dans le buffer
		{
			//ft_printf("Something on buffer %d %s",i, e->fds[i].buf_read );
			if (ft_strchr(e->fds[i].buf_read, '\n')) //Command complete
			{
				char *cmd;
				
				cmd = NULL;
				cmd = cmd_from_buffer(e->fds[i].buf_read);
				if (cmd)
				{
					ft_printf("Comande complete [%s] reste dans buffer [%s] ", cmd, e->fds[i].buf_read);
					input(e, i, cmd);
					free(cmd);
				}
			}
		}

		i++;
	}
}
