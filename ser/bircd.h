/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bircd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 05:12:58 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/11 01:42:35 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIRCD_H
# define BIRCD_H

# include <sys/select.h>
# include <stdio.h>
# include <libft.h>
# include <sys/socket.h>

# define XV(err,res,str)	(x_void(err,res,str))
# define X(err,res,str)		(x_int(err,res,str))
# define MAX(a,b)	((a > b) ? a : b)

# define FD_FREE			0
# define FD_SERV			1
# define FD_CLIENT			2
# define BUF_SIZE			2048
# define SPEED_MAX 			20
# define MAX_CMD_SIZE 		512
# define USAGE				"Usage: %s [port 9999]\n"
# define GENERAL_CHANNEL	"#general"
# define DEFAULT_NAME		"guest"

typedef struct	s_fd
{
	int			type;
	void		(*fct_read)();
	void		(*fct_write)();
	char		buf_read[BUF_SIZE + 1];
	char		buf_write[BUF_SIZE + 1];
	char		name[BUF_SIZE + 1];
	char		channel[BUF_SIZE + 1];
}				t_fd;

typedef struct	s_env
{
	t_fd		*fds;
	int			port;
	int			maxfd;
	int			max;
	int			r;
	fd_set		fd_read;
	fd_set		fd_write;
}				t_env;

void			init_env(t_env *e);
void			get_opt(t_env *e, int ac, char **av);
void			main_loop(t_env *e);
void			srv_create(t_env *e, int port);
void			srv_accept(t_env *e, int s);
void			client_read(t_env *e, int cs);
void			client_write(t_env *e, int cs);
void			clean_fd(t_fd *fd);
int				x_int(int err, int res, char *str);
void			*x_void(void *err, void *res, char *str);
void			init_fd(t_env *e);
void			do_select(t_env *e);
void			check_fd(t_env *e);

int				search_user(t_env *e, char *nick);
void			who_list(t_env *e, int cs);
void			input_message(t_env *e, int cs, char *buffer);
int				private_message(t_env *e, int cs, char *buffer);

void			input(t_env *e, int cs, char *buffer);
void			write_client(int sock, char *buffer);
void			presend(t_env *e, int cs, char *cmd);

#endif
