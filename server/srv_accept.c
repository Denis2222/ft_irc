
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bircd.h"

void			srv_accept(t_env *e, int s)
{
	int			cs;
	struct sockaddr_in	csin;
	socklen_t		csin_len;

	csin_len = sizeof(csin);
	cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");
	printf("New client #%d from %s:%d\n", cs, inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clean_fd(&e->fds[cs], cs);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;

	ft_strcpy(e->fds[cs].name,"guest[");
	ft_strcat(e->fds[cs].name, ft_itoa(cs));
	ft_strcat(e->fds[cs].name, "]");

	ft_printf("{red}%s{eoc}", e->fds[cs].name);
	char *connectmsg;

	connectmsg = ft_strjoin("NAME#", e->fds[cs].name);

	ft_printf("{red}%s{eoc}", connectmsg);
	send(cs, connectmsg, ft_strlen(connectmsg), 0);
	free(connectmsg);
}
