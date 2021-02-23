/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:23:00 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 20:23:04 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		my_pixel_put(t_all *all, int x, int y, int color)
{
	char *dst;

	dst = all->win.addr + (y * all->win.line_l + x * (all->win.bpp / 8));
	*(unsigned int*)dst = color;
}

int			get_color(t_tex_img *img, int x, int y)
{
	unsigned int *dst;

	if (x >= img->w || y >= img->h || x < 0 || y < 0)
		return (0);
	dst = img->addr + (y * img->line + x * (img->bpp / 8));
	return (*dst);
}
