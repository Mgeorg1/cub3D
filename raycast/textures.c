/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 00:30:09 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/26 00:30:12 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures(t_textures *t, void *mlx, t_all *all)
{
	t->img_n.img = mlx_xpm_file_to_image(mlx, t->fd_n,
					&t->img_n.w, &t->img_n.h);
	t->img_s.img = mlx_xpm_file_to_image(mlx, t->fd_s,
					&t->img_s.w, &t->img_s.h);
	t->img_e.img = mlx_xpm_file_to_image(mlx, t->fd_e,
					&t->img_e.w, &t->img_e.h);
	t->img_w.img = mlx_xpm_file_to_image(mlx, t->fd_w,
					&t->img_w.w, &t->img_w.h);
	t->img_sp.img = mlx_xpm_file_to_image(mlx, t->fd_sprite,
					&t->img_sp.w, &t->img_sp.h);
	if (!t->img_n.img || !t->img_s.img ||
		!t->img_e.img || !t->img_w.img || !t->img_sp.img)
		error("WRONG TEXTURES PATH!\n", all);
	t->img_n.addr = mlx_get_data_addr(t->img_n.img,
					&t->img_n.bpp, &t->img_n.line, &t->img_n.en);
	t->img_s.addr = mlx_get_data_addr(t->img_s.img,
					&t->img_s.bpp, &t->img_s.line, &t->img_s.en);
	t->img_e.addr = mlx_get_data_addr(t->img_e.img,
					&t->img_e.bpp, &t->img_e.line, &t->img_e.en);
	t->img_w.addr = mlx_get_data_addr(t->img_w.img,
					&t->img_w.bpp, &t->img_w.line, &t->img_w.en);
	t->img_sp.addr = mlx_get_data_addr(t->img_sp.img,
					&t->img_sp.bpp, &t->img_sp.line, &t->img_sp.en);
}
