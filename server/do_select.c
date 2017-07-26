
#include <stdlib.h>
#include "bircd.h"

void	do_select(t_env *e)
{
	printf("do_select()\n");
	e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}
