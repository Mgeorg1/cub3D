/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:38:45 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 21:38:47 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	key_w(t_all *all)
{
	if (all->map[(int)(all->plr.y - all->plr.pln.x
	* MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y -= all->plr.pln.x * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->plr.pln.y
	* MOVE_SPD)] != '1')
		all->plr.x += all->plr.pln.y * MOVE_SPD;
}

void	key_a(t_all *all)
{
	if (all->map[(int)(all->plr.y - all->plr.pln.y
	* MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y -= all->plr.pln.y * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x - all->plr.pln.x
	* MOVE_SPD)] != '1')
		all->plr.x -= all->plr.pln.x * MOVE_SPD;
}

void	key_s(t_all *all)
{
	if (all->map[(int)(all->plr.y + all->plr.pln.x
	* MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y += all->plr.pln.x * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x - all->plr.pln.y
	* MOVE_SPD)] != '1')
		all->plr.x -= all->plr.pln.y * MOVE_SPD;
}

void	key_d(t_all *all)
{
	if (all->map[(int)(all->plr.y + all->plr.pln.y
	* MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y += all->plr.pln.y * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->plr.pln.x
	* MOVE_SPD)] != '1')
		all->plr.x += all->plr.pln.x * MOVE_SPD;
}
