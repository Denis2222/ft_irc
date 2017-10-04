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

	char *buffer;

	buffer = NULL;
	buffer = ft_strnew(BUF_SIZE+1);

	res = recv(cs, buffer, BUF_SIZE, 0);
	if (res > 0 && ft_strlen(buffer))
	{
		buffer[res] = '\0';
		ft_printf("RECU [%s]", buffer);
		if (ft_strlen(buffer) <= MAX_CMD_SIZE)
			input(e, cs, buffer, res);
		ft_bzero(buffer, BUF_SIZE);
	}
	else
		clean_fd(&e->fds[cs], 0);

	buffer = NULL;
	free(buffer);
}
