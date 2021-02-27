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

void		window_open(t_all *all)
{
	all->win.win = mlx_new_window(all->win.mlx,
	all->win.w_res.w, all->win.w_res.h, "cub3d");
	init_textures(&all->tex, all->win.mlx, all);
	mlx_hook(all->win.win, 2, 0, press_key, all);
	mlx_hook(all->win.win, 3, 0, release_key, all);
	mlx_hook(all->win.win, 17, 0, exit_m, all);
	mlx_loop_hook(all->win.mlx, draw_screen, all);
	mlx_loop(all->win.mlx);
}

void		loop_h(t_all *all)
{
	mlx_hook(all->win.win, 2, 0, &press_key, all);
	mlx_hook(all->win.win, 3, 0, &release_key, all);
	mlx_hook(all->win.win, 17, 0, exit_m, all);
	mlx_loop_hook(all->win.mlx, draw_screen, all);
	mlx_loop(all->win.mlx);
}

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
