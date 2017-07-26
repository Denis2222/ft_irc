
#include <stdlib.h>
#include <sys/resource.h>
#include "bircd.h"

void		init_env(t_env *e)
	{
	int		i;
	struct rlimit	rlp;

	printf("init_env\n");
	X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");
	e->maxfd = rlp.rlim_cur;
	printf("e->maxfd=%d \n", e->maxfd);
	e->fds = (t_fd*)Xv(NULL, malloc(sizeof(*e->fds) * e->maxfd), "malloc");
	printf("e->fds malloced for maxfd\n");
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i], i);
		i++;
	}
	printf("e ready!\n");
}
