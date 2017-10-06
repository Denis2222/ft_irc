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

int read_server(t_client *client)
{
	int head;
	int res;

	head = ft_strlen(client->buf_read);
	res = recv(client->socket, &client->buf_read[head], 1, 0);
	if (res > 0)
	{
		client->buf_read[head+res] = 0;
		return (1);
	}
	else if (res < 0)
	{
		return (-1);
	}
	else
		return (0);
}
