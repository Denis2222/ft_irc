/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:56:43 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/11 06:24:51 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	server_write(t_client *e)
{
	char	tmp[BUF_SIZE + 1];
	int		res;
	int		length;

	length = ft_strlen(e->buf_write);
	if (length > SPEED_MAX)
		length = SPEED_MAX;
	res = send(e->socket, e->buf_write, length, 0);
	if (res > 0)
	{
		ft_bzero(tmp, BUF_SIZE + 1);
		ft_strcpy(tmp, &e->buf_write[res]);
		ft_bzero(e->buf_write, BUF_SIZE + 1);
		ft_strcpy(e->buf_write, tmp);
	}
	if (res == 0)
	{
		ft_printf("Server disconnect");
		exit(1);
	}
	return ;
}

void	presend(t_client *e, char *cmd)
{
	if (ft_strlen(e->buf_write) + ft_strlen(cmd) + 1 > BUF_SIZE)
	{
		return ;
	}
	if (ft_strlen(cmd) == 0)
		return ;
	ft_strcat(e->buf_write, cmd);
	ft_strcat(e->buf_write, "\n");
}
