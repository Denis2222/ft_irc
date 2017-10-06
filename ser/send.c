/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 06:39:04 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 10:55:02 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void presend(t_env *e, int cs, char *cmd)
{
	char *sc;

	sc = e->fds[cs].buf_write;
	if (ft_strlen(sc) + ft_strlen(cmd) > BUF_SIZE)
	{
		ft_printf("Buffer Overflow !!! Trash that or Disconnect this spam er!");
		ft_bzero(e->fds[cs].buf_write, BUF_SIZE);
		return ;
	}
	
	if (ft_strlen(sc))
		ft_strcat(sc, "\n");
	ft_strcat(sc, cmd);
}
