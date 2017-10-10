/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:53:51 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 03:29:00 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	render_text(t_client *client)
{
	t_msg *msg;

	msg = client->msg;
	while (msg)
	{
		wattron(client->chatbox, COLOR_PAIR(msg->color));
		waddstr(client->chatbox, msg->text);
		waddch(client->chatbox, '\n');
		wattroff(client->chatbox, COLOR_PAIR(msg->color));
		msg = msg->next;
	}
}

static void	view_info(t_client *client)
{
	char *nb;

	wmove(client->infobox, 1, 1);
	waddstr(client->infobox, "Nickname :");
	waddstr(client->infobox, client->name);
	waddstr(client->infobox, " | Channel :");
	waddstr(client->infobox, client->channel);
	waddstr(client->infobox, " | NB Message :");
	nb = ft_itoa(lenmsg(client->msg));
	waddstr(client->infobox, nb);
	free(nb);
}

void		view(t_client *client)
{
	WINDOW * cbox;
	WINDOW * pbox;
	if (NCURSE)
	{
		clear();
		cbox = subwin(stdscr, LINES - 5, COLS, 0, 0);
		pbox = subwin(stdscr, 4, COLS, LINES - 4, 0);
		client->infobox = subwin(stdscr, 3, COLS, LINES - 6, 0);
		client->chatbox = subwin(stdscr, LINES - 6, COLS - 2, 1, 1);
		client->promptbox = subwin(stdscr, 2, COLS - 2, LINES - 3, 1);
		scrollok(client->chatbox, TRUE);
		scrollok(client->promptbox, TRUE);
		render_text(client);
		wmove(client->promptbox, 0, 0);
		render_line(&client->lnbuffer, client->promptbox);
		view_info(client);
		box(client->infobox, ACS_VLINE, ACS_HLINE);
		box(cbox, ACS_VLINE, ACS_HLINE);
		box(pbox, ACS_VLINE, ACS_HLINE);
		wrefresh(client->chatbox);
		wrefresh(client->infobox);
		wrefresh(client->promptbox);
	}
}
