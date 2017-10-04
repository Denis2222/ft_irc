/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:42:07 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 16:00:42 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	char *buffer;
	buffer = NULL;

	size_t toread = 0;
	size_t read = 0;

	r = recv(cs, &toread, sizeof(size_t), 0);
	if (toread <= 0 && r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs], cs);
		printf("client #%d gone away [close & clean_fd ]\n", cs);
		return ;
	}
	ft_printf("\nReceive : %d octet\n", toread);
	buffer = ft_strnew(toread+1);
	while ((r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0)) > 0 && toread > 0)
	{
		read+= r;
		toread-=r;
		ft_strcat(buffer, e->fds[cs].buf_read);
		ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
		if (toread == 0)
			break;
	}
	ft_printf("{red}Buffer incoming : '%s' [%d]{eoc}\n", buffer, read);
	input(e, cs, buffer, read);
	buffer = NULL;
	free(buffer);
}
