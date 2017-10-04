/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 11:47:54 by dmoureu-         ###   ########.fr       */
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
	ft_printf("\nReceive : %d octet\n", toread);
	if (r <= 0 || toread == 0)
	{
		close(sock);
		ft_printf("Server gone Offline\n", sock);
		return(NULL);
	}
	buffer = ft_strnew(toread+1);
	ft_bzero(buf, BUFF_SIZE + 1);
	ft_printf("T OU PTAIN 1er");
	while ((r = recv(sock, buf, BUF_SIZE, 0)) > 0 && toread > 0)
	{
		ft_printf("Wololo  %d ", r);
		read+= r;
		toread-=r;
		ft_printf("T OU PTAIN2eme  %d %d", toread, read);
		ft_strcat(buffer, buf);
		ft_bzero(buf, BUF_SIZE);
		ft_printf("|%s|", buffer);
		if (toread == 0)
			break;
	}
	ft_printf("\nReceive : %d octet bis \n", toread);
	*n = read;
	return (buffer);
}

int sendall(int s, void *buf, size_t *len)
{
    size_t total = 0;        // how many bytes we've sent
    size_t bytesleft = *len; // how many we have left to send
    size_t n;

    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1)
		{
			break;
		}
        total += n;
        bytesleft -= n;
    }
    *len = total;
    if (n == -1)
		return (-1);
	return (0);
}

void write_server(int sock, const char *buffer)
{
	size_t i;
	size_t sizeoftruc;

	sizeoftruc = sizeof(size_t);
	i = ft_strlen(buffer);
	if (i > 0)
	{
		sendall(sock, &i,&sizeoftruc );
		sendall(sock, (char *)buffer, &i);
	}
}
