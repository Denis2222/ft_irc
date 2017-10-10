/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 04:20:58 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 05:10:59 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bircd.h"

int		x_int(int err, int res, char *str)
{
	if (res == err)
	{
		ft_dprintf(STDERR_FILENO, "%s error (%s, %d): %s\n",
		str, strerror(errno));
		exit(1);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str)
{
	if (res == err)
	{
		ft_dprintf(STDERR_FILENO, "%s error (%s, %d): %s\n",
		str, strerror(errno));
		exit(1);
	}
	return (res);
}
