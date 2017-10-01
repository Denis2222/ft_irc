/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 06:27:07 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/06/11 06:29:53 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "bircd.h"

void	main_loop(t_env *e)
{
	printf("\nmain_loop:\n");
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}