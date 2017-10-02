#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;
	char *buffer;

	printf("client_read(e,%d)\n", cs);
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	buffer = (char*)malloc(r+1);
	bzero(buffer, r+1);
	strncpy(buffer, e->fds[cs].buf_read, r);
	printf("recv() = %d\n", r);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs], cs);
		printf("client #%d gone away [close & clean_fd ]\n", cs);
	}
	else
	{
		ft_printf("{red}Buffer incoming : '%s' [%d]{eoc}\n", buffer, r);

		if (buffer[0] == '/')
		{
			char **tab;

			tab = ft_strsplit(buffer, ' ');
			//Command
			if (ft_strnstr(buffer, "/nick ", 6))
			{
				ft_strcpy(e->fds[cs].name, tab[1]);
				send(cs, buffer, ft_strlen(buffer), 0);
			}
			if (ft_strnstr(buffer, "/channel ", 9))
			{
				ft_strcpy(e->fds[cs].channel, tab[1]);
				send(cs, buffer, ft_strlen(buffer), 0);
			}

			ft_printf("%s %s\n", e->fds[cs].channel, e->fds[cs].name);
			ft_tabfree(tab);
		}
		else
		{
			i = 0;
			while (i < e->maxfd)
			{
				if (e->fds[i].type == FD_CLIENT)	//Send to all other
				{
					if (1 || (i != cs)) // Not him
					{
						//ft_printf("Send To %d %s %s", ft_strcmp(e->fds[i].channel, e->fds[cs].channel),e->fds[cs].channel, e->fds[i].channel );
						if (ft_strcmp(e->fds[i].channel, e->fds[cs].channel) == 0) // Only same channel
						{
							//ft_printf("Send good ");
							char *msg;

							//ft_printf("{red}DEBUG:%s %d{eoc}\n", buffer, ft_strlen(buffer));
							msg = ft_mprintf("/newmsg #[%s][%s]:%s", e->fds[cs].channel, e->fds[cs].name, buffer);
							send(i, msg, ft_strlen(msg), 0);
							free(msg);
							printf("send to [%d]\n", i);
						}
					}
				}
				i++;
			}
		}
	}
	buffer = NULL;
	free(buffer);
}
