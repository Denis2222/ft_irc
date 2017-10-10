/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msghelp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 03:11:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/10 03:12:18 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	showmsghelp(t_client *client)
{
	writemsg(client, "        =========================");
	writemsg(client, "        ====== IRCLIENT2000 =====");
	writemsg(client, "        =========================");
	writemsg(client, "        /connect [machine] [port]");
	writemsg(client, "        /disconnect");
	writemsg(client, "        /nick [name] min:3 max:9");
	writemsg(client, "        /who");
	writemsg(client, "        /join [channel]");
	writemsg(client, "        /leave");
	writemsg(client, "        /quit");
	writemsg(client, "        /help");
}
