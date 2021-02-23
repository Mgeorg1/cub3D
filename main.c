#include "includes/cub3d.h"
#include <stdio.h>
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

int exit_m(t_all *all)
{
	free_all(all);
	exit(0);
}

void 	init_v(t_all *all)
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
	key_init(all);
}

void window_open(t_all *all)
{
	all->win.win = mlx_new_window(all->win.mlx, all->win.w_res.w, all->win.w_res.h, "cub3d");
	init_textures(&all->tex, all->win.mlx, all);
	mlx_hook(all->win.win, 2, 0, press_key, all);
	mlx_hook(all->win.win, 3, 0, release_key, all);
	mlx_hook(all->win.win, 17 , 0, exit_m, all);
	mlx_loop_hook(all->win.mlx, draw_screen, all);
	mlx_loop(all->win.mlx);
}

void	loop_h(t_all *all)
{
	mlx_hook(all->win.win, 2, 0, &press_key, all);
	mlx_hook(all->win.win, 3, 0, &release_key, all);
	mlx_hook(all->win.win, 17, 0, exit_m, all);
	mlx_loop_hook(all->win.mlx, draw_screen, all);
	mlx_loop(all->win.mlx);
}

int		is_cub_file(char *arg, t_all *all)
{
	char *tmp;

	tmp = arg + ft_strlen(arg) - 4;
	if (ft_strncmp(tmp, ".cub", 5))
		error("it is not \".cub\" file", all);
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
	if(!(all->win.win = mlx_new_window(all->win.mlx, all->win.w_res.w, all->win.w_res.h, "cub3d")))
		error("MEMMORY ALLOCATE ERROR!\n", all);
	loop_h(all);
}

int 	main(int argc, char *argv[])
{
	t_all all;
	int		fd;

	init_v(&all);
	all.win.mlx = mlx_init();
	if (argc < 2 && argc > 4)
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