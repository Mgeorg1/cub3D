/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 00:52:41 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/26 00:52:43 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	m_free(char **words)
{
	int i;

	i = 0;
	if (words != NULL)
	{
		while (words[i])
		{
			free(words[i]);
			i++;
		}
		free(words);
		words = NULL;
	}
}

void	my_destroy_img(t_all *all, t_tex_img *t)
{
	if (all->win.mlx && t->img)
		mlx_destroy_image(all->win.mlx, t->img);
}

void	free_all(t_all *all)
{
	if (all->spr)
		free(all->spr);
	if (all->spr_vis)
		free(all->spr_vis);
	if (all->map_lst != NULL)
		ft_lstclear(&all->map_lst, free);
	m_free(all->map);
	if (all->z_buf != NULL)
		free(all->z_buf);
	if (all->win.mlx && all->win.win)
		mlx_destroy_window(all->win.mlx, all->win.win);
	my_destroy_img(all, &all->tex.img_n);
	my_destroy_img(all, &all->tex.img_s);
	my_destroy_img(all, &all->tex.img_e);
	my_destroy_img(all, &all->tex.img_w);
	my_destroy_img(all, &all->tex.img_sp);
}

int		exit_m(t_all *all)
{
	free_all(all);
	exit(0);
}

void	init_v(t_all *all)
{
	all->map = NULL;
	all->line = NULL;
	all->spr = NULL;
	all->sp_num = 0;
	all->spr = NULL;
	all->spr_vis = NULL;
	all->win.scr_res.w = 2560;
	all->win.scr_res.h = 1440;
	all->z_buf = NULL;
	all->win.mlx = NULL;
	all->win.win = NULL;
	all->win.img = NULL;
	all->tex.img_e.img = NULL;
	all->tex.img_s.img = NULL;
	all->tex.img_n.img = NULL;
	all->tex.img_w.img = NULL;
	all->tex.img_sp.img = NULL;
	all->plr.dir.x = 0;
	all->plr.dir.y = 0;
	all->plr.pln.x = 0;
	all->plr.pln.y = 0;
	all->save_f = 0;
	all->map_lst = NULL;
	key_init(all);
}
