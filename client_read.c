#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;


	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs], cs);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		printf(" fd: %d maxfd: %d  %s \n",cs, e->maxfd, e->fds[cs].buf_read);
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) && (i != cs))
			{
				send(i, e->fds[cs].buf_read, r, 0);
				printf("send to [%d]\n", i);
			}
			i++;
		}
	}
}
