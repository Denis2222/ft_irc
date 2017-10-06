/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:56:43 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 17:15:06 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	server_write(t_client *e)
{
    char tmp[BUF_SIZE + 1]; 
    int res;

    res = send(e->socket, e->buf_write, 1, 0);
    if (res > 0)
    {
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
		ft_printf("Buffer Overflow !!! Trash that or Disconnect this spam er!");
		return ;
	}
	if (ft_strlen(sc))
		ft_strcat(sc, "\n");
	ft_strcat(sc, cmd);
}