/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:44:55 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 21:44:57 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sp(t_spr *x, int first, int last)
{
	int		pivot;
	int		i;
	int		j;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (x[i].dist <= x[pivot].dist && i < last)
				i++;
			while (x[j].dist > x[pivot].dist)
				j--;
			if (i < j)
				swap_sp(x, j, i);
		}
		swap_sp(x, j, pivot);
		sort_sp(x, first, j - 1);
		sort_sp(x, j + 1, last);
	}
}

void	is_visible(t_all *all)
{
	int j;
	int i;

	i = 0;
	j = 0;
	while (i < all->sp_num)
	{
		if (all->spr[i].dist < VIEW_DIST)
		{
			all->spr_vis[j] = all->spr[i];
			j++;
		}
		i++;
	}
	all->sp_num_v = j;
}

void	calc_spr(t_all *all, t_sp_cast *sp, int i)
{
	sp->spr_pl.x = all->spr_vis[i].pos.x - all->plr.x;
	sp->spr_pl.y = all->spr_vis[i].pos.y - all->plr.y;
	sp->inv_det = 1.0 /
	(all->plr.pln.x * all->plr.dir.y - all->plr.dir.x * all->plr.pln.y);
	sp->transf.x = sp->inv_det *
	(all->plr.dir.y * sp->spr_pl.x - all->plr.dir.x * sp->spr_pl.y);
	sp->transf.y = sp->inv_det *
	(-all->plr.pln.y * sp->spr_pl.x + all->plr.pln.x * sp->spr_pl.y);
	sp->sp_screen_x = (int)((all->win.w_res.w / 2) *
	(1 + sp->transf.x / sp->transf.y));
	sp->sp_h = abs((int)(all->win.w_res.w * OPT_RATIO / sp->transf.y));
	sp->draw_start_y = -sp->sp_h / 2 + all->win.w_res.h / 2;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->sp_h / 2 + all->win.w_res.h / 2;
	if (sp->draw_end_y >= all->win.w_res.h)
		sp->draw_end_y = all->win.w_res.h - 1;
	sp->sp_w = abs((int)(all->win.w_res.w * OPT_RATIO / sp->transf.y));
	sp->draw_start_x = -sp->sp_w / 2 + sp->sp_screen_x;
	if (sp->draw_start_x < 0)
		sp->draw_start_x = 0;
	sp->draw_end_x = sp->sp_w / 2 + sp->sp_screen_x;
	if (sp->draw_end_x > all->win.w_res.w)
		sp->draw_end_x = all->win.w_res.w - 1;
}

void	draw_spr_stripe(t_all *all, t_sp_cast *sp)
{
	int x;
	int y;

	x = sp->draw_start_x;
	while (x <= sp->draw_end_x)
	{
		sp->tex.x = (int)((256 * (x - (-sp->sp_w / 2 + sp->sp_screen_x))
		* all->tex.img_sp.w / sp->sp_w) / 256);
		if (sp->transf.y > 0 && x >= 0
		&& x < all->win.w_res.w && sp->transf.y < all->z_buf[x])
		{
			y = sp->draw_start_y;
			while (y <= sp->draw_end_y)
			{
				sp->d = y * 256 - all->win.w_res.h * 128 + sp->sp_h * 128;
				sp->tex.y = ((sp->d * all->tex.img_sp.h) / sp->sp_h) / 256;
				sp->color = get_color(&all->tex.img_sp,
				sp->tex.x, sp->tex.y);
				if ((sp->color & 0x00FFFFFF) != 0)
					my_pixel_put(all, x, y, sp->color);
				y++;
			}
		}
		x++;
	}
}

void	draw_sprites(t_all *all)
{
	int			i;
	t_sp_cast	sp;

	i = 0;
	while (i < all->sp_num)
	{
		all->spr[i].dist = pow(all->plr.x - all->spr[i].pos.x, 2)
		+ pow(all->plr.y - all->spr[i].pos.y, 2);
		i++;
	}
	is_visible(all);
	i = all->sp_num_v;
	sort_sp(all->spr_vis, 0, all->sp_num_v - 1);
	while (i >= 0 && all->sp_num > 0)
	{
		calc_spr(all, &sp, i);
		draw_spr_stripe(all, &sp);
		i--;
	}
}
