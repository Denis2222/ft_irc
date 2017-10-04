/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/04 11:05:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void render_text(t_client *client)
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

static void view(t_client *client)
{

	client->infobox = subwin(stdscr, 3, COLS, LINES -6, 0);
	client->chatbox = subwin(stdscr, LINES -5, COLS, 0, 0);
	client->promptbox = subwin(stdscr, 4, COLS, LINES -4, 0);
	scrollok(client->chatbox, TRUE);
	scrollok(client->promptbox, TRUE);

	//mvwprintw(client->promptbox, 1, 1, "Nickname");

	render_text(client);

	wmove(client->promptbox, 1, 1);
	render_line(&client->lnbuffer, client->promptbox);

	wmove(client->infobox, 1, 1);
	waddstr(client->infobox, "Nickname :");
	waddstr(client->infobox, client->name);
	waddstr(client->infobox, " | Channel :");
	waddstr(client->infobox, client->channel);
	waddstr(client->infobox, " | NB Message :");
	//waddstr(client->infobox, ft_itoa(lenmsg(client->msg)));//LEAKS

	box(client->infobox, ACS_VLINE, ACS_HLINE);
	box(client->chatbox, ACS_VLINE, ACS_HLINE);
	box(client->promptbox, ACS_VLINE, ACS_HLINE);


	wrefresh(client->chatbox);
	wrefresh(client->infobox);
	wrefresh(client->promptbox);

}

static void events(t_client *client)
{
	char ln[PROMPT_SIZE_MAX];
	int len = 0;

	len = get_line_non_blocking(&client->lnbuffer, ln, sizeof(ln));
	if(len > 0) {
		if(strcmp(ln, "exit") == 0) {
			//break;
			ft_printf("Exit ask");
		}
		cmd_out(ln, client);
	}
	clear();
	view(client);
}

int loop_connect(fd_set *rdfs, t_client *client)
{
	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(client->socket, rdfs);
	if (select(client->socket + 1, rdfs, NULL, NULL, NULL) == -1)
	{
		dprintf(STDERR_FILENO, "select() error");
		perror("select()");
		exit(1);
		return (1);
	}
	if (FD_ISSET(STDIN_FILENO, rdfs))
	{
		events(client);
	}

	if (FD_ISSET(client->socket, rdfs))
	{
	   cmd_in(client);
	   events(client);
   }
   return (1);
}

int loop_disconnect(t_client *client)
{
	char	*line;
	char buffer[BUF_SIZE];

	get_next_line_single(STDIN_FILENO, &line);
	ft_strcpy(buffer, line);
	cmd_out(buffer, client);
	free(line);
	line = NULL;
	return (1);
}
