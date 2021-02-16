#include "includes/cub3d.h"
#define SCALE_M 5
#define MOVE_SPD 0.07
#define VIEW_DIST 5000.0
#include  <stdio.h>

void	my_pixel_put(t_all *all, int x, int y, int color)
{
	char *dst;
	
	dst = all->win.addr + (y * all->win.line_l + x * (all->win.bpp / 8));
	*(unsigned int*)dst = color;
}


void	init_textures(t_textures *t, void *mlx, t_all *all)
{
		t->img_n.img = mlx_xpm_file_to_image(mlx, t->fd_n, &t->img_n.w, &t->img_n.h);
		t->img_s.img = mlx_xpm_file_to_image(mlx, t->fd_s, &t->img_s.w, &t->img_s.h);
		t->img_e.img = mlx_xpm_file_to_image(mlx, t->fd_e, &t->img_e.w, &t->img_e.h);
		t->img_w.img = mlx_xpm_file_to_image(mlx, t->fd_w, &t->img_w.w, &t->img_w.h);
		t->img_sp.img = mlx_xpm_file_to_image(mlx, t->fd_sprite, &t->img_sp.w, &t->img_sp.h);
		if (!t->img_n.img || !t->img_s.img || !t->img_e.img || !t->img_w.img || !t->img_sp.img)
			error("WRONG TEXTURES PATH!\n", all);
		t->img_n.addr = mlx_get_data_addr(t->img_n.img, &t->img_n.bpp, &t->img_n.line, &t->img_n.en);
		t->img_s.addr = mlx_get_data_addr(t->img_s.img, &t->img_s.bpp, &t->img_s.line, &t->img_s.en);
		t->img_e.addr = mlx_get_data_addr(t->img_e.img, &t->img_e.bpp, &t->img_e.line, &t->img_e.en);
		t->img_w.addr = mlx_get_data_addr(t->img_w.img, &t->img_w.bpp, &t->img_w.line, &t->img_w.en);
		t->img_sp.addr = mlx_get_data_addr(t->img_sp.img, &t->img_sp.bpp, &t->img_sp.line, &t->img_sp.en);
}

int		get_color(t_tex_img *img, int x, int y)
{
	unsigned int *dst;

	dst = img->addr + (y * img->line + x * (img->bpp / 8));
	return (*dst);
}

// void draw_map(t_all *all, t_point point, int color)
// {
// 	int end_x;
// 	int end_y;
	
// 	end_x = (point.x + 1) * SCALE_M;
// 	end_y = (point.y + 1) * SCALE_M;
// 	point.x *= SCALE_M;
// 	point.y *= SCALE_M;
// 	while (point.y < end_y)
// 	{	
// 		while (point.x < end_x)
// 		{
// 			my_pixel_put(all, point.x, point.y, color);
// 			point.x++;
// 		}
// 		point.y++;
// 		point.x -= SCALE_M;
// 	} 
// }

// void draw_line(t_all *all, int len_r, int wall_x, int c)
// {
// 	int wall_h;
// 	int wall_s;

// 	if (len_r == 0)
// 		len_r++;
// 	wall_h =  all->win.win_res.height * 4 / len_r;
// 	wall_s =  all->win.win_res.height / 2 - wall_h / 2;
// 	while (wall_s <= (all->win.win_res.height / 2 + wall_h / 2))
// 		my_pixel_put(all, wall_x, wall_s++, c);
// }

// void	ft_cast_ray(t_all *all)
// {
// 	t_plr ray = all->plr;
// 	double start;
// 	double end;

// 	start = all->plr.dir1 - 0.5;
// 	end = all->plr.dir1 + 0.5;
// 	int color = 0x7B0099;
// 	while (start <= end)
// 	{
// 		ray = all->plr;
// 		ray.y *= SCALE_M;
// 		ray.x *= SCALE_M;
// 		ray.x += SCALE_M / 2;
// 		while (all->map[(int)(ray.y / SCALE_M)][(int)(ray.x / SCALE_M)] != '1')
// 		{
// 			ray.x += cos(start);
// 			ray.y += sin(start);
// 			my_pixel_put(all, ray.x, ray.y, color);
// 			//len_r++;
// 		}
// 		//draw_line(all, len_r, wall_x, c);
// 		//len_r = 0;
// 		//wall_x++;
// 		start += 1.0 / 10000;
// 	}
	
// }

// void draw_player(t_plr *plr, t_all *all)
// {
// 	int end_x;
// 	int end_y;
// 	t_plr  p;
// 	p = *plr;
// 	end_x = (p.x + 1) * SCALE_M;
// 	end_y = (p.y + 1) * SCALE_M;
// 	p.x *= SCALE_M;
// 	p.y *= SCALE_M;
// 	ft_cast_ray(all);
// 	while (p.y < end_y)
// 	{	
// 		while (p.x < end_x)
// 		{
// 			my_pixel_put(all, p.x , p.y, 0x000099);
// 			p.x++;
// 		}
// 		p.y++;
// 		p.x -= SCALE_M;
// 	}
// }

void	draw_ver_line(int x, int start, int end, int color, t_all *all)
{
	while (start <= end)
	{
		my_pixel_put(all, x, start, color);
		start++;
	}
}

void	ray_init(t_all *all, t_ray *ray)
{
	ray->camera_x = 2 * ray->x / (double)(all->win.win_res.width) - 1;
	ray->ray_dir.x = all->plr.dir.x + all->plr.plane.x * ray->camera_x;
	ray->ray_dir.y = all->plr.dir.y + all->plr.plane.y * ray->camera_x;
	ray->map_p.y = (int)all->plr.y;
	ray->map_p.x = (int)all->plr.x;
	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	ray->hit = 0;
}

void	cell_intersects_calc(t_all *all, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (all->plr.x - ray->map_p.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_p.x + 1.0 - all->plr.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (all->plr.y - ray->map_p.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_p.y + 1.0 - all->plr.y) * ray->delta_dist.y;
	}
}


void	dda(t_all *all, t_ray *ray)
{
	cell_intersects_calc(all, ray);
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_p.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_p.y += ray->step.y;
			ray->side = 1;
		}
		if (all->map[ray->map_p.y][ray->map_p.x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_p.x - all->plr.x + (1 - ray->step.x) / 2) / ray->ray_dir.x;
	else
		ray->perp_wall_dist = (ray->map_p.y - all->plr.y + (1 - ray->step.y) / 2) / ray->ray_dir.y;
}

void	draw_floor(int x, int end, int c, t_all *all)
{

	while (end < all->win.win_res.height && end >= 0)
	{
		my_pixel_put(all, x, end, c);
		end++;
	}
}

void	draw_celling(int x, int start, int c, t_all *all)
{
	int i;

	i = 0;
	while (i < start)
	{
		my_pixel_put(all, x, i, c);
		i++;
	}
}

t_tex_img *get_side(t_ray *ray, t_all *all)
{
	t_tex_img *t;

	if (ray->side == 0)
	{
		if (ray->step.x > 0)
			t = &all->textures.img_e;
		else
			t = &all->textures.img_w;
	}
	else
	{
		if (ray->step.y > 0)
			t = &all->textures.img_s;
		else
			t = &all->textures.img_n;

	}
	return (t);
}

void	sort_sp(t_spr *x, int first, int last)
{
	t_spr	tmp;
	int		pivot;
	int 	i;
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
			{
				tmp = x[i];
				x[i] = x[j];
				x[j] = tmp;
			}
		}
		tmp = x[pivot];
		x[pivot] = x[j];
		x[j] = tmp;
		sort_sp(x, first, j - 1);
		sort_sp(x, j + 1, last);
	}
}

// void	sort_sp(t_spr *a, int n)
// {
// 	int i;
// 	int j;
// 	t_spr tmp;

// 	i = 0;
// 	while(i < (n - 1))
// 	{
// 		j = 0;
// 		while (j < n - i - 1)
// 		{
// 			if (a[j].dist < a[j + 1].dist)
// 			{
// 				tmp = a[j];
// 				a[j] = a[j + 1];
// 				a[j + 1] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

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

void	draw_sprites(t_all *all)
{
	int i;
	int j;
	int stripe;
	t_sp_cast sp;
	int d;

	i = 0;
	while(i < all->sp_num)
	{
		all->spr[i].dist = pow(all->plr.x - all->spr[i].pos.x , 2) + pow(all->plr.y - all->spr[i].pos.y, 2);
		i++;
	}
	is_visible(all);
	//i = 0;
	i = all->sp_num_v;
	sort_sp(all->spr_vis, 0, all->sp_num_v - 1);
	//sort_sp(all->spr_vis, all->sp_num_v);
	//while (i < all->sp_num_v)
	while (i >= 0)
	{
			sp.spr_pl.x = all->spr_vis[i].pos.x - all->plr.x;
			sp.spr_pl.y = all->spr_vis[i].pos.y - all->plr.y;
			sp.inv_det = 1.0 / (all->plr.plane.x * all->plr.dir.y - all->plr.dir.x * all->plr.plane.y);
			sp.transf.x = sp.inv_det * (all->plr.dir.y * sp.spr_pl.x - all->plr.dir.x * sp.spr_pl.y);
			sp.transf.y = sp.inv_det * (-all->plr.plane.y * sp.spr_pl.x + all->plr.plane.x * sp.spr_pl.y);
			sp.sp_screen_x = (int)((all->win.win_res.width / 2) * (1 + sp.transf.x / sp.transf.y));
			sp.sp_h = abs((int)(all->win.win_res.height / sp.transf.y));
			sp.draw_start_y = -sp.sp_h / 2 + all->win.win_res.height / 2;
			if (sp.draw_start_y < 0)
				sp.draw_start_y = 0;
			sp.draw_end_y = sp.sp_h / 2 + all->win.win_res.height / 2;
			if (sp.draw_end_y >= all->win.win_res.height)
				sp.draw_end_y = all->win.win_res.height - 1;
			sp.sp_w = abs((int)(all->win.win_res.height / sp.transf.y));
			sp.draw_start_x = -sp.sp_w / 2 + sp.sp_screen_x;
			if (sp.draw_start_x < 0)
				sp.draw_start_x = 0;
			sp.draw_end_x = sp.sp_w / 2 + sp.sp_screen_x;
			if (sp.draw_end_x > all->win.win_res.width)
				sp.draw_end_x = all->win.win_res.width - 1;
			stripe = sp.draw_start_x;
			while (stripe < sp.draw_end_x)
			{
				sp.tex.x = (int)((256 * (stripe - (-sp.sp_w / 2 + sp.sp_screen_x)) * all->textures.img_sp.w / sp.sp_w) / 256);
				if (sp.transf.y > 0 && stripe > 0 && stripe < all->win.win_res.width && sp.transf.y < all->z_buf[stripe])
				{
					j = sp.draw_start_y;
					while (j < sp.draw_end_y)
					{
						d = j * 256 - all->win.win_res.height * 128 + sp.sp_h * 128;
						sp.tex.y = ((d * all->textures.img_sp.h) / sp.sp_h) / 256;
						sp.color = get_color(&all->textures.img_sp, sp.tex.x, sp.tex.y);
						if ((sp.color & 0x00FFFFFF) != 0)
							my_pixel_put(all, stripe, j, sp.color);
						j++;
					}
				}
				stripe++;
			}
		//i++;
		i--;
	}
}

void	draw_walls(t_all *all)
{
	t_ray	ray;
	t_tex_img *t;
	ray.x = 0;
	while (ray.x < all->win.win_res.width)
	{
		ray_init(all, &ray);
		dda(all, &ray);
		ray.l_height = (int) (all->win.win_res.height / ray.perp_wall_dist);
		ray.draw_start = -1 * ray.l_height / 2 + all->win.win_res.height / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.l_height / 2 + all->win.win_res.height / 2;
		if (ray.draw_end  >= all->win.win_res.height)
			ray.draw_end = all->win.win_res.height - 1;
		if (ray.side == 0)
			ray.wall_x = all->plr.y + ray.perp_wall_dist * ray.ray_dir.y;
		else
			ray.wall_x = all->plr.x + ray.perp_wall_dist * ray.ray_dir.x;
		t = get_side(&ray, all);
		ray.wall_x -= floor(ray.wall_x);
		ray.tex_x = (int)(ray.wall_x * (double)t->w);
		if (ray.side == 0 && ray.ray_dir.x > 0)
			ray.tex_x = t->w - ray.tex_x - 1;
		else if (ray.side == 1 && ray.ray_dir.y < 0)
			ray.tex_x = t->w - ray.tex_x - 1;
		ray.step_tex = 1.0 * t->w / ray.l_height;
		ray.tex_pos = (ray.draw_start - all->win.win_res.height / 2 + ray.l_height / 2) * ray.step_tex;
		
		draw_floor(ray.x, ray.draw_end, all->c_floor, all);
		draw_celling(ray.x, ray.draw_start, all->c_celling, all);
		while (ray.draw_start < ray.draw_end)
		{
			ray.tex_y = (int)ray.tex_pos & (t->h - 1);
			ray.tex_pos += ray.step_tex;
			ray.color = get_color(t, ray.tex_x, ray.tex_y);
			my_pixel_put(all, ray.x, ray.draw_start, ray.color);
			ray.draw_start++;
		}
		all->z_buf[ray.x] = ray.perp_wall_dist;
		ray.x++;
	}
}

void	key_init(t_all *all)
{
	all->keys.w = 0;
	all->keys.a = 0;
	all->keys.s = 0;
	all->keys.d = 0;
	all->keys.left_arrow = 0;
	all->keys.right_arrow = 0;
}

void	key_w(t_all *all)
{
	if (all->map[(int)(all->plr.y  - all->plr.plane.x * MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y -= all->plr.plane.x * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->plr.plane.y * MOVE_SPD)] != '1')
		all->plr.x += all->plr.plane.y * MOVE_SPD;
}

void	key_a(t_all *all)
{
	if (all->map[(int)(all->plr.y  - all->plr.plane.y * MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y -= all->plr.plane.y * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x - all->plr.plane.x * MOVE_SPD)] != '1')
		all->plr.x -= all->plr.plane.x * MOVE_SPD;
}

void	key_s(t_all *all)
{
	if (all->map[(int)(all->plr.y  + all->plr.plane.x * MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y += all->plr.plane.x * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x - all->plr.plane.y * MOVE_SPD)] != '1')
		all->plr.x -= all->plr.plane.y * MOVE_SPD;
}

void	key_d(t_all *all)
{
	if (all->map[(int)(all->plr.y  + all->plr.plane.y * MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y += all->plr.plane.y * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->plr.plane.x * MOVE_SPD)] != '1')
		all->plr.x += all->plr.plane.x * MOVE_SPD;
}

void	key_left(t_all *all)
{
	t_vec tmp;

	tmp = all->plr.dir;
	all->plr.dir.x = all->plr.dir.x * cos(-0.1) - all->plr.dir.y * sin(-0.1);
	all->plr.dir.y = tmp.x * sin(-0.1) + all->plr.dir.y * cos(-0.1);
	tmp = all->plr.plane;
	all->plr.plane.x = tmp.x * cos(-0.1) - tmp.y * sin(-0.1);
	all->plr.plane.y = tmp.x * sin(-0.1) + tmp.y * cos(-0.1);
}

void	key_right(t_all *all)
{
	t_vec	tmp;

	tmp = all->plr.dir;
	all->plr.dir.x = all->plr.dir.x * cos(0.1) - all->plr.dir.y * sin(0.1);
	all->plr.dir.y = tmp.x * sin(0.1) + all->plr.dir.y * cos(0.1);
	tmp = all->plr.plane;
	all->plr.plane.x = tmp.x * cos(0.1) - tmp.y * sin(0.1);
	all->plr.plane.y = tmp.x * sin(0.1) + tmp.y * cos(0.1);
}

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
	my_destroy_img(all, &all->textures.img_n);
	my_destroy_img(all, &all->textures.img_s);
	my_destroy_img(all, &all->textures.img_e);
	my_destroy_img(all, &all->textures.img_w);
	my_destroy_img(all, &all->textures.img_sp);
}

int exit_m(t_all *all)
{
	free_all(all);
	exit(0);
}

void	check_key_flags(t_all *all)
{
	if (all->keys.w == 1)
		key_w(all);
	if (all->keys.a == 1)
		key_a(all);
	if (all->keys.s == 1)
		key_s(all);
	if (all->keys.d == 1)
		key_d(all);
	if (all->keys.left_arrow == 1)
		key_left(all);
	if (all->keys.right_arrow == 1)
		key_right(all);
}

int		press_key(int keycode, t_all *all)
{
	if (keycode == 13)
		all->keys.w = 1;
	if (keycode == 0)
		all->keys.a = 1;
	if (keycode == 2)
		all->keys.d = 1;
	if (keycode == 1)
		all->keys.s = 1;
	if (keycode == 123)
		all->keys.left_arrow = 1;
	if (keycode == 124)
		all->keys.right_arrow = 1;
	 //up - 126 down - 125 left - 123 right - 124
	if (keycode == 53)
		exit_m(all);
	return (0);
}

int		release_key(int keycode, t_all *all)
{
	if (keycode == 13)
		all->keys.w = 0;
	if (keycode == 0)
		all->keys.a = 0;
	if (keycode == 2)
		all->keys.d = 0;
	if (keycode == 1)
		all->keys.s = 0;
	if (keycode == 123)
		all->keys.left_arrow = 0;
	if (keycode == 124)
		all->keys.right_arrow = 0;
	return (0);
}

int 	draw_screen(t_all *all)
{
	t_point point;

	check_key_flags(all);
	all->win.img = mlx_new_image(all->win.mlx, all->win.win_res.width, all->win.win_res.height);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bpp, &all->win.line_l, &all->win.en);
	draw_walls(all);
	draw_sprites(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	mlx_destroy_image(all->win.mlx, all->win.img);
	return (0);
}

void	draw_in_bmp(t_all *all)
{
	t_point point;

	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bpp, &all->win.line_l, &all->win.en);
	//init bmp;
	draw_walls(all);
	draw_sprites(all);
	//put in bmp;
	mlx_destroy_image(all->win.mlx, all->win.img);
}

void 	init_v(t_all *all)
{
	all->map = NULL;
	all->line = NULL;
	all->spr = NULL;
	all->sp_num = 0;
	all->spr = NULL;
	all->spr_vis = NULL;
	all->win.scr_res.width = 2560;
	all->win.scr_res.height = 1440;
	all->z_buf = NULL;
	all->win.mlx = NULL;
	all->win.win = NULL;
	all->win.img = NULL;
	all->textures.img_e.img = NULL;
	all->textures.img_s.img = NULL;
	all->textures.img_n.img = NULL;
	all->textures.img_w.img = NULL;
	all->textures.img_sp.img = NULL;
	key_init(all);
}

void window_open(t_all *all)
{
	all->win.win = mlx_new_window(all->win.mlx, all->win.win_res.width, all->win.win_res.height, "cub3d");
	init_textures(&all->textures, all->win.mlx, all);
	mlx_hook(all->win.win, 2, 0, press_key, all);
	mlx_hook(all->win.win, 3, 0, release_key, all);
	mlx_hook(all->win.win, 17 , 0, exit_m, all);
	mlx_loop_hook(all->win.mlx, draw_screen, all);
	mlx_loop(all->win.mlx);
}

void	get_sqrns(t_all *all)
{
	init_textures(&all->textures, all->win.mlx, all);

}

void	loop_h(t_all *all)
{
	mlx_hook(all->win.win, 2, 0, &press_key, all);
	mlx_hook(all->win.win, 3, 0, &release_key, all);
	mlx_hook(all->win.win, 17, 0, exit_m, all);
	mlx_loop_hook(all->win.mlx, draw_screen, all);
	mlx_loop(all->win.mlx);
}

int 	main(int argc, char *argv[])
{
	t_all all;
	int		fd;

	init_v(&all);
	all.win.mlx = mlx_init();
	//mlx_get_screen_size(all.win.mlx, &all.win.scr_res.width, &all.win.scr_res.height);
	if (argc < 2 && argc > 3)
		error("WRONG NUMBER OF ARGUMENTS!\n", &all);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error("NO SUCH FILE OR DIRECTORY!\n", &all);
	if (parser(fd, &all) < 0)
		error("SOMTHING WRONG WITH .cub FILE!\n", &all);
	if (!(all.z_buf = (double*)malloc(all.win.win_res.width * sizeof(double))))
		error("MEMMORY ALLOCATE ERROR!\n", &all);
	if(!(all.win.win = mlx_new_window(all.win.mlx, all.win.win_res.width, all.win.win_res.height, "cub3d")))
		error("MEMMORY ALLOCATE ERROR!\n", &all);
	init_textures(&all.textures, all.win.mlx, &all);
	loop_h(&all);
	
}