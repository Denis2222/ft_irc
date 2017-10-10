/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 03:11:17 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	init_client(t_client *client)
{
	client->connect = 0;
	client->msg = NULL;
	client->lines_read = 0;
	client->exit = 1;
	ft_strcpy(client->name, "");
	ft_strcpy(client->channel, "");
	ft_bzero(client->buf_write, BUF_SIZE + 1);
	ft_bzero(client->buf_read, BUF_SIZE + 1);
	make_buffer(&client->lnbuffer);
}

static void	init_ncurse(void)
{
	if (NCURSE)
	{
		initscr();
		start_color();
		cbreak();
		nonl();
		timeout(0);
		keypad(stdscr, 1);
		noecho();
		curs_set(0);
		intrflush(stdscr, 0);
		leaveok(stdscr, 1);
		clear();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_BLUE, COLOR_BLACK);
	}
}

static void	end_ncurse(void)
{
	if (NCURSE)
	{
		delwin(stdscr);
		endwin();
	}
}

int			main(int ac, char **argv)
{
	t_client client;

	init_client(&client);
	init_ncurse();
	showmsghelp(&client);
	if (ac > 1)
		tryconnect(&client, ac, argv);
	view(&client);
	refresh();
	while (42)
		if (!loop(&client))
			break ;
	close(client.socket);
	destroy_buffer(&client.lnbuffer);
	end_ncurse();
	return (0);
}
