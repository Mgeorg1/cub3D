/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 00:49:18 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/26 00:49:20 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	write_image(t_all *all, int fd)
{
	int y;

	y = all->win.w_res.h;
	while (y >= 0)
	{
		y--;
		write(fd, all->win.line_l * y + all->win.addr, all->win.line_l);
	}
	close(fd);
	free_all(all);
	exit(EXIT_SUCCESS);
}

void	write_info(t_all *all, int fd)
{
	unsigned int	n;
	unsigned int	i;
	short			b;

	n = all->win.line_l * (all->win.w_res.h) + 54;
	write(fd, "BM", 2);
	write(fd, &n, 4);
	i = 0;
	write(fd, &i, 4);
	i = 54;
	write(fd, &i, 4);
	i = 40;
	write(fd, &i, 4);
	write(fd, &all->win.w_res.w, 4);
	write(fd, &all->win.w_res.h, 4);
	b = 1;
	write(fd, &b, 2);
	b = all->win.bpp;
	write(fd, &b, 2);
	i = 0;
	write(fd, &i, 4);
	write(fd, &i, 4);
	write(fd, &i, 4);
	write(fd, &i, 4);
	write(fd, &i, 4);
}

void	make_bmp(t_all *all)
{
	int				fd;

	if ((fd = open("cub3d.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666)) < 0)
		error("FAIL WITH CREATING FILE!\n", all);
	write_info(all, fd);
	write_image(all, fd);
}
