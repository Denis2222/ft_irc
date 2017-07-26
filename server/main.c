/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 06:27:01 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/06/11 06:29:57 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int	main(int ac, char **av)
{
	t_env	e;

	printf("main\n");
	init_env(&e);
	get_opt(&e, ac, av);
	srv_create(&e, e.port);
	printf("main\n");
	main_loop(&e);
	return (0);
}
