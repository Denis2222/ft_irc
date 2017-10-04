
#include <stdlib.h>
#include "bircd.h"

void	do_select(t_env *e)
{
	struct timeval timeout;

	timeout.tv_sec = 30;
	e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, &timeout);
}
