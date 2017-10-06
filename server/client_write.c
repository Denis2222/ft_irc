#include <sys/socket.h>
#include "bircd.h"

void	client_write(t_env *e, int cs)
{
    char tmp[BUF_SIZE + 1]; 
    int res;

    res = send(cs, e->fds[cs].buf_write, 10, 0);
    if (res > 0)
    {
        ft_strcpy(tmp, &e->fds[cs].buf_write[res]);
        ft_printf("T LA BATARD ? %s",tmp);
        ft_bzero(e->fds[cs].buf_write, BUF_SIZE + 1);
        ft_strcpy(e->fds[cs].buf_write, tmp);
    }
	if (res == 0)
	{
		ft_printf("Client %d disconnect", cs);
		clean_fd(&e->fds[cs], cs);
    }
    return ;
}
