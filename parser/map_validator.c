/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:40:42 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/23 17:40:47 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	line_validator(t_all *all, int x, int y)
{
	if (all->dir_flag > 1)
		error("THE PLAYER DIRECTION MUST BE ONE!\n", all);
	if (x > 0 && (y + 1) < all->map_len
	&& (x + 1) < ft_strlen(all->map[y]) && y > 0)
	{
		if (x >= ft_strlen(all->map[y + 1]) || x >= ft_strlen(all->map[y - 1]))
			error("THE MAP IS NOT CLOSED!\n", all);
		if (all->map[y][x - 1] == ' ' || all->map[y][x + 1] == ' '
		|| all->map[y - 1][x] == ' '
		|| all->map[y + 1][x] == ' ' || all->map[y - 1][x - 1] == ' '
		|| all->map[y - 1][x + 1] == ' '
		|| all->map[y + 1][x - 1] == ' ' || all->map[y + 1][x + 1] == ' '
		|| all->map[y + 1][x + 1] == '\0' || all->map[y - 1][x + 1] == '\0')
			error("THE MAP IS NOT CLOSED!\n", all);
	}
	else
		error("THE MAP IS NOT CLOSED!\n", all);
}

void	get_start_dir(t_all *all, char c, int x, int y)
{
	all->plr.x = x + 0.5;
	all->plr.y = y + 0.5;
	all->dir_flag++;
	if (c == 'E')
	{
		all->plr.dir.x = 1;
		all->plr.pln.y = 0.66;
	}
	if (c == 'W')
	{
		all->plr.dir.x = -1;
		all->plr.pln.y = -0.66;
	}
	if (c == 'N')
	{
		all->plr.dir.y = -1;
		all->plr.pln.x = 0.66;
	}
	if (c == 'S')
	{
		all->plr.dir.y = 1;
		all->plr.pln.x = -0.66;
	}
}

int		join_spr(t_all *all, int sp_count, int x, int y)
{
	t_spr	*sp;

	sp = all->spr;
	sp[sp_count].pos.x = x + 0.5;
	sp[sp_count].pos.y = y + 0.5;
	return (++sp_count);
}

void	map_validator(t_all *all, int x, int y, int sp_count)
{
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (all->map[y][x] == ' ' || all->map[y][x] == '1')
				x++;
			if (all->map[y][x] == '0' || all->map[y][x] == 'N' ||
			all->map[y][x] == 'S' || all->map[y][x] == 'W' ||
			all->map[y][x] == 'E' || all->map[y][x] == '2')
			{
				if (all->map[y][x] == 'N' || all->map[y][x] == 'S'
				|| all->map[y][x] == 'W' || all->map[y][x] == 'E')
					get_start_dir(all, all->map[y][x], x, y);
				if (all->map[y][x] == '2')
					sp_count = join_spr(all, sp_count, x, y);
				line_validator(all, x, y);
				x++;
			}
		}
		y++;
	}
	if (all->dir_flag == 0)
		error("THE PLAYER DIRECTION MUST BE ONE!\n", all);
}
