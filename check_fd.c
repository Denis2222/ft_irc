
#include "bircd.h"

void	check_fd(t_env *e)
{
	int	i;

	i = 0;
	printf("check_fd(): e->r = %d\n", e->r);
	while ((i < e->maxfd) && (e->r > 0))
	{
		if (FD_ISSET(i, &e->fd_read))
		{
			printf("FD_ISSET(%d, fd_read)\n", i);
			e->fds[i].fct_read(e, i);
		}
		if (FD_ISSET(i, &e->fd_write))
		{
			printf("FD_ISSET(%d, fd_write)\n", i);
			e->fds[i].fct_write(e, i);
		}
		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->r--;
		i++;
	}
}
