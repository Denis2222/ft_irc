/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 10:40:19 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void init_client(t_client *client)
{
	client->connect = 0;
	client->msg = NULL;
	ft_strcpy(client->name, "");
	ft_strcpy(client->channel, "");
	client->lines_read = 0;

	make_buffer(&client->lnbuffer);
}

int main(int ac, char **argv)
{
	t_client client;
	fd_set	rdfs;

	init_client(&client);

/*
	FILE *f = fopen("/dev/ttys001", "r+");
  	SCREEN *debug = newterm(NULL, stdout, f);


	SCREEN *screen = newterm(NULL, f, stdin);*/
	//struct screen scr = initscr();

	initscr();
	//newterm(NULL, stdout, stdin);
	start_color();
    cbreak();             // Immediate key input
    nonl();               // Get return key
    timeout(0);           // Non-blocking input
    keypad(stdscr, 1);    // Fix keypad
    noecho();             // No automatic printing
    curs_set(0);          // Hide real cursor
    intrflush(stdscr, 0); // Avoid potential graphical issues
    leaveok(stdscr, 1);   // Don't care where cursor is left

	//clear();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);

	if (ac == 3)
	{
		connect_host(argv[1], argv[2], &client);
		client.connect = 1;
	}
	while(42)
	{
		if (client.connect)
		{
			//ft_printf("While 42 loop\n");
			if (!loop_connect(&rdfs, &client))
				break;
		}
		else
			loop_disconnect(&client);
	}
	close(client.socket);
	destroy_buffer(&client.lnbuffer);
	delwin(stdscr);
	endwin();
	refresh();
	return (0);
}
