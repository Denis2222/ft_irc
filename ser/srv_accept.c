/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 04:19:00 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 06:57:19 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bircd.h"

static void	srv_accept_msg(t_env *e, int cs)
{
	char	*connectmsg;

	connectmsg = ft_mprintf("/nick %s\n/join %s \n",
		e->fds[cs].name, e->fds[cs].channel);
	ft_printf("Send all %s", connectmsg);
	presend(e, cs, connectmsg);
	free(connectmsg);
	presend(e, cs, "/newmsg ===================\n");
	presend(e, cs, "/newmsg ===================\n");
	presend(e, cs, "/newmsg [Server]Welcome IRC\n");
	presend(e, cs, "/newmsg ===================\n");
	presend(e, cs, "/newmsg ===================\n");
}

void		srv_accept(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;
	char				*name;

	csin_len = sizeof(csin);
	cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");
	ft_printf("New client #%d from %s:%d\n",
		cs, inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clean_fd(&e->fds[cs]);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	ft_strcpy(e->fds[cs].name, DEFAULT_NAME);
	name = ft_itoa(cs);
	ft_strcat(e->fds[cs].name, name);
	free(name);
	ft_strcat(e->fds[cs].name, "");
	ft_strcpy(e->fds[cs].channel, GENERAL_CHANNEL);
	ft_bzero(e->fds[cs].buf_read, BUF_SIZE + 1);
	ft_bzero(e->fds[cs].buf_write, BUF_SIZE + 1);
	ft_printf("{red}%s{eoc}", e->fds[cs].name);
	srv_accept_msg(e, cs);
}
