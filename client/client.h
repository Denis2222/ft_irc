/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 07:48:58 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/02 18:43:32 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>//close
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>//strlen
#include <libft.h>

#include <ctype.h>
#include <ncurses.h>

#define BUF_SIZE	1024
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define PORT 8067

struct input_line {
    char *ln;
    int length;
    int capacity;
    int cursor;
    int last_rendered;
};

typedef struct		s_msg
{
	char 			*text;
	struct s_msg	*next;
}					t_msg;

typedef struct		s_client
{
	int 			lines_read;
	int				connect;
	struct hostent	*hostinfo;
	int				socket;
	struct sockaddr_in sin;
	char 			name[BUF_SIZE+1];
	char			channel[BUF_SIZE+1];

	WINDOW			*chatbox;
	WINDOW			*promptbox;
	WINDOW			*infobox;
	struct input_line lnbuffer;

	t_msg			*msg;

}					t_client;

int connect_host(char *host, char *port, t_client *client);
int checkhost(t_client *client);
int checksocket (t_client *client);
int connectsocket(t_client *client, char *port);

int cmd_out(char *line, t_client *client);
int cmd_in(t_client *client, char *cmd);

int read_server(int sock, char *buffer);
void send_server(int sock, char *cmd);
void write_server(int sock, const char *buffer);

int loop_connect(fd_set *rdfs, t_client *client);
int loop_disconnect(t_client *client);


void make_buffer(struct input_line *buf);
void destroy_buffer(struct input_line *buf);
void render_line(struct input_line *buf, WINDOW *win);
int retrieve_content(struct input_line *buf, char *target, int max_len);
void add_char(struct input_line *buf, char ch);
int handle_input(struct input_line *buf, char *target, int max_len, int key);
int get_line_non_blocking(struct input_line *buf, char *target, int max_len);


t_msg	*newmsg(char *text);
t_msg	*addmsg(t_msg **lstmsg, t_msg *msg);
int		lenmsg(t_msg *msg);
