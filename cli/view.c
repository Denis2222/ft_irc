/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:53:51 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/06 14:17:57 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void render_text(t_client *client)
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

void view(t_client *client)
{
	if (NCURSE)
	{
		clear();
		client->infobox = subwin(stdscr, 3, COLS, LINES -6, 0);
		client->chatbox = subwin(stdscr, LINES -5, COLS, 0, 0);
		client->promptbox = subwin(stdscr, 4, COLS, LINES -4, 0);
		scrollok(client->chatbox, TRUE);
		scrollok(client->promptbox, TRUE);
		render_text(client);
		wmove(client->promptbox, 1, 1);
		render_line(&client->lnbuffer, client->promptbox);
		wmove(client->infobox, 1, 1);
		waddstr(client->infobox, "Nickname :");
		waddstr(client->infobox, client->name);
		waddstr(client->infobox, " | Channel :");
		waddstr(client->infobox, client->channel);
		waddstr(client->infobox, " | NB Message :");
		box(client->infobox, ACS_VLINE, ACS_HLINE);
		box(client->chatbox, ACS_VLINE, ACS_HLINE);
		box(client->promptbox, ACS_VLINE, ACS_HLINE);
		wrefresh(client->chatbox);
		wrefresh(client->infobox);
		wrefresh(client->promptbox);
	}
}
