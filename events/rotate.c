/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:40:49 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 21:40:51 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	key_left(t_all *all)
{
	t_vec tmp;

	tmp = all->plr.dir;
	all->plr.dir.x = all->plr.dir.x * cos(-0.1) - all->plr.dir.y * sin(-0.1);
	all->plr.dir.y = tmp.x * sin(-0.1) + all->plr.dir.y * cos(-0.1);
	tmp = all->plr.pln;
	all->plr.pln.x = tmp.x * cos(-0.1) - tmp.y * sin(-0.1);
	all->plr.pln.y = tmp.x * sin(-0.1) + tmp.y * cos(-0.1);
}

void	key_right(t_all *all)
{
	t_vec	tmp;

	tmp = all->plr.dir;
	all->plr.dir.x = all->plr.dir.x * cos(0.1) - all->plr.dir.y * sin(0.1);
	all->plr.dir.y = tmp.x * sin(0.1) + all->plr.dir.y * cos(0.1);
	tmp = all->plr.pln;
	all->plr.pln.x = tmp.x * cos(0.1) - tmp.y * sin(0.1);
	all->plr.pln.y = tmp.x * sin(0.1) + tmp.y * cos(0.1);
}
