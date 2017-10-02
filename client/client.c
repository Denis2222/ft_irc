/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/02 16:15:19 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static init_client(t_client *client)
{
	client->connect = 0;
	ft_strcpy(client->name, "");
	ft_strcpy(client->channel, "");
	ft_printf("{green}====CLIRC START===={eoc}\n");
	ft_printf("Connect to server : /connect [host] [port]\n");
}

int main(int ac, char **argv)
{
	t_client client;
	fd_set	rdfs;

	init_client(&client);
	if (ac == 3)
	{
		connect_host(argv[1], argv[2], &client);
		client.connect = 1;
	}
	while(42)
	{
		if (client.connect)
		{
			if (!loop_connect(&rdfs, &client))
				break;
		}
		else
			loop_disconnect(&client);
	}
	close(client.socket);
	return (0);
}
