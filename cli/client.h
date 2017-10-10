/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 07:48:58 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 03:40:04 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/socket.h>
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <libft.h>

# include <ctype.h>
# include <ncurses.h>

# define BUF_SIZE		1024
# define INVALID_SOCKET	-1
# define SOCKET_ERROR	-1
# define PORT			8067
# define PROMPT_SIZE_MAX	500
# define MAX_MSG			100
# define SPEED_MAX		20

# define NCURSE 1

typedef struct			s_input_line {
	char				*ln;
	int					length;
	int					capacity;
	int					cursor;
	int					last_rendered;
}						t_inline;

typedef struct			s_msg
{
	char				*text;
	struct s_msg		*next;
	int					color;
}						t_msg;

typedef struct			s_client
{
	int					lines_read;
	int					connect;
	int					exit;
	struct hostent		*hostinfo;
	int					socket;
	struct sockaddr_in	sin;
	char				name[BUF_SIZE + 1];
	char				channel[BUF_SIZE + 1];

	WINDOW				*chatbox;
	WINDOW				*promptbox;
	WINDOW				*infobox;
	t_inline			lnbuffer;

	t_msg				*msg;
	char				buffer[BUF_SIZE + 1];

	char				buf_read[BUF_SIZE + 1];
	char				buf_write[BUF_SIZE + 1];
	fd_set				fd_read;
	fd_set				fd_write;
}						t_client;

void					tryconnect(t_client *client, int ac, char **argv);
int						connect_host(char *host, char *port, t_client *client);
int						checkhost(t_client *client, char *host);
int						checksocket (t_client *client);
int						connectsocket(t_client *client, char *port);

int						cmd_out(char *line, t_client *client);
int						cmd_in(t_client *client);

int						read_server(t_client *client);
void					send_server(int sock, char *cmd);
void					write_server(int sock, char *buffer);

void					server_write(t_client *e);
void					presend(t_client *e, char *cmd);

int						loop(t_client *client);

void					make_buffer(t_inline *buf);
void					destroy_buffer(t_inline *buf);
void					render_line(t_inline *buf, WINDOW *win);
int						retrieve_content(t_inline *buf, char *target,
	int max_len);
void					add_char(t_inline *buf, char ch);
int						handle_input(t_inline *buf, char *target, int max_len,
	int key);
int						get_line_non_blocking(t_inline *buf, char *target,
	int max_len);

t_msg					*newmsg(char *text, t_client *client);
t_msg					*addmsg(t_msg **lstmsg, t_msg *msg);
int						lenmsg(t_msg *msg);
void					writemsg(t_client *client, char *cmd);
void					showmsghelp(t_client *client);

void					view(t_client *client);
#endif
