/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 00:58:35 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/26 00:58:38 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		is_cub_file(char *arg, t_all *all)
{
	char *tmp;

	tmp = arg + ft_strlen(arg) - 4;
	if (ft_strncmp(tmp, ".cub", 5))
		error("it is not \".cub\" file!\n", all);
	return (0);
}

void	flag_save(t_all *all, int fd)
{
	all->save_f = 1;
	parser(fd, all);
	if (!(all->z_buf = (double*)malloc(all->win.w_res.w * sizeof(double))))
		error("MEMMORY ALLOCATE ERROR!\n", all);
	init_textures(&all->tex, all->win.mlx, all);
	draw_screen(all);
	make_bmp(all);
}

void	game_start(t_all *all, int fd)
{
	parser(fd, all);
	if (!(all->z_buf = (double*)malloc(all->win.w_res.w * sizeof(double))))
		error("MEMMORY ALLOCATE ERROR!\n", all);
	init_textures(&all->tex, all->win.mlx, all);
	if (!(all->win.win = mlx_new_window(all->win.mlx,
	all->win.w_res.w, all->win.w_res.h, "cub3d")))
		error("MEMMORY ALLOCATE ERROR!\n", all);
	loop_h(all);
}

int		main(int argc, char *argv[])
{
	t_all	all;
	int		fd;

	init_v(&all);
	all.win.mlx = mlx_init();
	if (argc < 2 || argc > 3)
		error("WRONG NUMBER OF ARGUMENTS!\n", &all);
	if ((fd = open(argv[1], O_RDONLY)) < 0 || is_cub_file(argv[1], &all))
		error("NO SUCH FILE OR DIRECTORY!\n", &all);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
		flag_save(&all, fd);
	else if (argc == 3)
		error("UNKNOWN FLAG\n", &all);
	else
		game_start(&all, fd);
}
