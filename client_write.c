#include <sys/socket.h>
#include "bircd.h"

void	client_write(t_env *e, int cs)
{
	int r;
	char buffer[4096];
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE - 1, 0);
	if (r > 0)
	{
//		ft_printf("message receive");
	}
	buffer[r] = 0;
}
