/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/02 00:51:35 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int read_server(int sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      exit(1);
   }

   buffer[n] = 0;

   return n;
}

static void send_server(int sock, char *cmd)
{
	//ft_printf("Send %d, %s", ft_strlen(cmd), cmd);
   	if(send(sock, cmd, strlen(cmd), 0) < 0)
   	{
    	perror("send()");
    	//exit(1);
   	}
}

static void write_server(int sock, const char *buffer)
{
	int offset;
	int allsend;
	char *packet;

	allsend = 0;
	offset = 0;
	//ft_printf("size of buffer: %d size int :%d", ft_strlen(buffer), sizeof(unsigned int));

	if (ft_strlen(buffer) > BUF_SIZE)
	{
		while (allsend == 0) {
			packet = ft_strsub(buffer, offset, BUF_SIZE);
			send_server(sock, (char *)packet);
			if (ft_strlen(packet) < BUF_SIZE)
			{
				allsend = 1;
			} else {
				offset += BUF_SIZE;
			}
			free(packet);
		}
	} else {
		send_server(sock, (char *)buffer);
	}
}

int command(char *line, t_client *client, int *connect)
{
   char **cmd;

   if (ft_strnstr(line, "/connect ", 9))
   {
	  //ft_printf("Join Command");
	  cmd = ft_strsplit(line, ' ');
	  ft_printf("connect to : %s ...\n", cmd[1]);
	  if (connect_host(cmd[1], cmd[2], client))
		*connect = 1;
   } else {
		if (*connect) {
			write_server(client->socket, line);
		}
   }
   return (0);
}

int receive_cmd(t_client *client, char *cmd)
{
	ft_printf("|{green}%s{eoc}|\n", cmd);
	char **tab;
	char **cmds;
	int i;

	i = 0;
	cmds = ft_strsplit(cmd, '\n');
	while (cmds[i] != '\0')
	{
		if (cmds[i][0] == '/') {
			tab = ft_strsplit(cmds[i], ' ');
			if (ft_strnstr(cmds[i], "/nick ", 6))
			{
				ft_strcpy(client->name, tab[1]);
			}
			if (ft_strnstr(cmds[i], "/channel ", 9))
			{
				ft_strcpy(client->channel, tab[1]);
			}
			ft_tabfree(tab);
		}
		i++;
	}
	ft_tabfree(cmds);
}

int main(int ac, char **argv)
{
	t_client client;
	int connect;

	ft_strcpy(client.name, "");
	ft_strcpy(client.channel, "");

	connect = 0;
	ft_printf("{green}====CLIRC START===={eoc}\n");
	ft_printf("Connect to server : /connect [host] [port]\n");

	char buffer[BUF_SIZE];
	fd_set	rdfs;

	if (ac == 3)
	{
		connect_host(argv[1], argv[2], &client);
		connect = 1;
	}
	while(42)
	{
		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);
		FD_SET(client.socket, &rdfs);
		ft_printf("#[%s][%s]: ", client.channel, client.name);

		if (select(client.socket + 1, &rdfs, NULL, NULL, NULL) == -1)
 	   	{
 		   dprintf(STDERR_FILENO, "select() error");
 		   return (1);
 	   	}
		if (FD_ISSET(STDIN_FILENO, &rdfs))
		{
			char	*line;
			get_next_line_single(STDIN_FILENO, &line);
			ft_strcpy(buffer, line);
			command(buffer, &client, &connect);
			free(line);
			line = NULL;
		}

		if (FD_ISSET(client.socket, &rdfs))
		{
			int n = read_server(client.socket, buffer);
			if (n == 0)
			{
			   ft_printf("server disconnected");
			   break;
		   }
		   receive_cmd(&client, buffer);
	   }
	}
	close(client.socket);
	return (0);
}
