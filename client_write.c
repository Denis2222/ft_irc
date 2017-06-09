#include <sys/socket.h>
#include "bircd.h"

void	client_write(t_env *e, int cs)
{
	int r;
	char buffer[4096];

	printf("client_write(e,%d)\n", cs);
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE - 1, 0);
	if (r > 0)
	{
		printf("message receive%s", buffer );
	}
	buffer[r] = 0;
}
