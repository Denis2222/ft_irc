/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:56:43 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/06 15:04:58 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	server_write(t_client *e)
{
    char tmp[BUF_SIZE + 1];
    int res;

	bzero(tmp, BUF_SIZE + 1);
    res = send(e->socket, e->buf_write, SPEED_MAX, 0);
	e->msg = addmsg(&e->msg, newmsg(ft_mprintf(">>>%s<<<",e->buf_write), e));
    if (res > 0)
    {
		e->buf_write[res] = 0;
		e->msg = addmsg(&e->msg, newmsg(ft_mprintf(">>2>%s<<<",e->buf_write), e));
        ft_strcpy(tmp, &e->buf_write[res]);
        ft_bzero(e->buf_write, BUF_SIZE + 1);
        ft_strcpy(e->buf_write, tmp);
    }
	if (res == 0)
	{
		ft_printf("Server disconnect");
    }
    return ;
}

void presend(t_client *e, char *cmd)
{
	char *sc;

	sc = e->buf_write;
	if (ft_strlen(sc) + ft_strlen(cmd) > BUF_SIZE)
	{
		ft_printf("Buffer Overflow !!! Trash that or Disconnect this spam er [%s] !", e->buf_write);
		return ;
	}
	if (ft_strlen(sc))
		ft_strcat(sc, "\n");
	ft_strcat(sc, cmd);
	//printf(">>>%s<<<", e->buf_write);
}
