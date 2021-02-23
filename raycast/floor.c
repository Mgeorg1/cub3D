/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:27:22 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 20:27:24 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		draw_floor(int x, int end, int c, t_all *all)
{
	while (end < all->win.w_res.h && end >= 0)
	{
		my_pixel_put(all, x, end, c);
		end++;
	}
}

void		draw_celling(int x, int start, int c, t_all *all)
{
	int i;

	i = 0;
	while (i < start)
	{
		my_pixel_put(all, x, i, c);
		i++;
	}
}
