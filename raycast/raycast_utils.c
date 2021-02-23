/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:28:43 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 20:28:48 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_tex_img	*get_side(t_ray *ray, t_all *all)
{
	t_tex_img *t;

	if (ray->side == 0)
	{
		if (ray->step.x > 0)
			t = &all->tex.img_e;
		else
			t = &all->tex.img_w;
	}
	else
	{
		if (ray->step.y > 0)
			t = &all->tex.img_s;
		else
			t = &all->tex.img_n;
	}
	return (t);
}

void		swap_sp(t_spr *x, int j, int i)
{
	t_spr tmp;

	tmp = x[i];
	x[i] = x[j];
	x[j] = tmp;
}
