#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include "bircd.h"

void			srv_create(t_env *e, int port)
{
	int			s;
	struct sockaddr_in	sin;
	struct protoent	*pe;

	pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname");

	printf("getprotobyname():\n return struct protoent protoent->name:%s\n protoent->p_proto:%d\n", pe->p_name, pe->p_proto);

	s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
	printf("socket() : %d \n", s);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	printf("\nstruct sockaddr_in:\nsin_family=AF_INET\nsin_addr.s_addr=INADDR_ANY\nsin_port=htons(%d)\n\n", port);
	X(-1, bind(s, (struct sockaddr*)&sin, sizeof(sin)), "bind");
	printf("bind(socket [%d], &sin, size of sin)\n", s);
	X(-1, listen(s, 42), "listen");
	printf("listen(socket [%d])\n", s);
	e->fds[s].type = FD_SERV;
	e->fds[s].fct_read = srv_accept;

	printf("e->fds[%d].type = FD_SERV\ne->fds[%d].fct_read = srv_accept\n", s,s);
}
