/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 04:09:30 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 04:09:32 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "bircd.h"

void	get_opt(t_env *e, int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf(USAGE, av[0]);
		exit(1);
	}
	e->port = ft_atoi(av[1]);
}
