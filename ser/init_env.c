
#include <stdlib.h>
#include <sys/resource.h>
#include "bircd.h"

void		init_env(t_env *e)
{
	int		i;
	struct rlimit	rlp;

	X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");
	e->maxfd = rlp.rlim_cur;
	e->fds = (t_fd*)Xv(NULL, malloc(sizeof(*e->fds) * e->maxfd), "malloc");
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i], i);
		ft_bzero(e->fds[i].buf_read, BUF_SIZE + 1);
		ft_bzero(e->fds[i].buf_write, BUF_SIZE + 1);
		i++;
	}
}
