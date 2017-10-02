/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/02 19:53:45 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void render_text(t_client *client)
{
	t_msg *msg;

	msg = client->msg;
	while (msg)
	{
		waddstr(client->chatbox, msg->text);
		waddch(client->chatbox, '\n');
		msg = msg->next;
	}
}

static void view(t_client *client)
{
	clear();
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
	waddstr(client->infobox, ft_itoa(lenmsg(client->msg)));//LEAKS

	box(client->infobox, ACS_VLINE, ACS_HLINE);
	box(client->chatbox, ACS_VLINE, ACS_HLINE);
	box(client->promptbox, ACS_VLINE, ACS_HLINE);


	wrefresh(client->chatbox);
	wrefresh(client->infobox);
	wrefresh(client->promptbox);

}

static void events(t_client *client)
{
	char ln[1024];
	int len = get_line_non_blocking(&client->lnbuffer, ln, sizeof(ln));
	if(len > 0) {
		if(strcmp(ln, "exit") == 0) {
			//break;
			ft_printf("Exit ask");
		}
		cmd_out(ln, client);
		mvaddstr(7 + client->lines_read, 5, ln);
		client->lines_read ++;
	}
	view(client);
}

int loop_connect(fd_set *rdfs, t_client *client)
{
	char buffer[BUF_SIZE];
	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(client->socket, rdfs);
	//ft_printf("#[%s][%s]: ", client->channel, client->name);

	if (select(client->socket + 1, rdfs, NULL, NULL, NULL) == -1)
	{
	   dprintf(STDERR_FILENO, "select() error");
	   return (1);
	}
	if (FD_ISSET(STDIN_FILENO, rdfs))
	{
		events(client);
		/*char	*line;
		get_next_line_single(STDIN_FILENO, &line);
		ft_strcpy(buffer, line);
		cmd_out(buffer, client);
		free(line);
		line = NULL;*/
	}

	if (FD_ISSET(client->socket, rdfs))
	{
		int n = read_server(client->socket, buffer);
		if (n == 0)
		{
		   ft_printf("server disconnected");
		   return (0);
	   }
	   cmd_in(client, buffer);
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
