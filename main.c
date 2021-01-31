/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:09:41 by aemustaf          #+#    #+#             */
/*   Updated: 2021/01/22 13:09:43 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#define SCALE 6
void	my_pixel_put(t_all *all, int x, int y, int color)
{
	char *dst;

	dst = all->win.addr + (y * all->win.line_l + x * (all->win.bpp / 8));
	*(unsigned int*)dst = color;
}

typedef struct 	s_vars
{
	void *mlx;
	void *win;
}				t_vars;
void	init_vars(t_vars *vars, t_all *all)
{
	ft_putchar_fd('s', 1);
	vars->mlx = mlx_init();
	ft_putchar_fd('s', 1);
	vars->win = mlx_new_window(vars->mlx, all->win.win_res.width, all->win.win_res.height, "WOFLENSTEIN");
}
int		main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	t_list	*map;
	t_all	all;
	char	**tmp;
	int x = 0;
	int y = 0;
	line = NULL;
	map = NULL;
	t_vars vars;
	
	all.win.scr_res.height = 1080;
	all.win.scr_res.width = 1920;
	init_vars(&vars, &all);
	if (argc < 2 && argc > 3)
		error("WRONG NUMBER OF ARGUMENTS!\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error("NO SUCH FILE OR DIRECTORY!\n");
	if (parser(fd, line, &map, &all) < 0)
		error("SOMTHING WRONG WITH .cub FILE!\n");
	/*---------------------<test>----------------------*/
	
	ft_putchar_fd('s', 1);
	while(all.map[y])
	{
		while (all.map[y][x])
		{
			mlx_pixel_put(vars.mlx, vars.win, x, y, 0xF00000);
			x++;
		}
		y++;
		x = 0;
	}
	mlx_put_image_to_window(all.win.mlx, all.win.win, all.win.win, 0, 0);
	ft_putchar_fd('s', 1);
    mlx_loop(vars.mlx);
	/*---------------------</test>----------------------*/
}
