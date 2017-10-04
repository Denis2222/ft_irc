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

void write_client(int sock, char *buffer)
{
	size_t i;
	size_t sizeoftruc = sizeof(size_t);
	i = ft_strlen(buffer);
	if (i > 0)
	{
		sendall(sock, &i,&sizeoftruc );
		sendall(sock, buffer, &i);
	} else {
		ft_printf("TENVOI DE LA MERDE!!!");
	}
}
