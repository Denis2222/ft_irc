/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 06:27:07 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 04:18:22 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	main_loop(t_env *e)
{
	ft_printf("FT_IRC Ready on port [%d]:\n", e->port);
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}
