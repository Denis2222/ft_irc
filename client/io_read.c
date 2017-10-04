/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 17:17:46 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char *read_server(int sock, int *n)
{
	int	r;
	char buf[BUFF_SIZE+1];
	char *buffer;

	size_t toread = 0;
	size_t read = 0;

	buffer = NULL;
	r = recv(sock, &toread, sizeof(size_t), 0);
	if (r <= 0 || toread == 0)
	{
		close(sock);
		ft_printf("Server gone Offline\n", sock);
		return(NULL);
	}
	buffer = ft_strnew(toread+1);
	ft_bzero(buf, BUFF_SIZE + 1);
	while ((r = recv(sock, buf, BUF_SIZE, 0)) > 0 && toread > 0)
	{
		read += r;
		toread -= r;
		ft_strcat(buffer, buf);
		ft_bzero(buf, BUF_SIZE);
		if (toread == 0)
			break;
	}
	*n = read;
	return (buffer);
}
