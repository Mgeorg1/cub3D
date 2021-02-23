/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:32:17 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 19:32:21 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		draw_screen(t_all *all)
{
	void	*img;
	void	*addr;
	t_point	point;

	check_key_flags(all);
	img = mlx_new_image(all->win.mlx, all->win.w_res.w, all->win.w_res.h);
	if (!img)
		error("MEMMORY ALLOCATE ERROR!\n", all);
	all->win.img = img;
	addr = mlx_get_data_addr(all->win.img, &all->win.bpp,
	&all->win.line_l, &all->win.en);
	if (!addr)
		error("MEMMORY ALLOCATE ERROR!\n", all);
	all->win.addr = addr;
	draw_walls(all);
	draw_sprites(all);
	if (all->save_f == 0)
	{
		mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
		mlx_destroy_image(all->win.mlx, all->win.img);
	}
	return (0);
}
