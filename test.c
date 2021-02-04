#include "includes/cub3d.h"
#define SCALE_M 5
#define MOVE_SPD 0.1
#include  <stdio.h>

void	my_pixel_put(t_all *all, int x, int y, int color)
{
	char *dst;

	dst = all->win.addr + (y * all->win.line_l + x * (all->win.bpp / 8));
	*(unsigned int*)dst = color;
}




void draw_map(t_all *all, t_point point, int color)
{
	int end_x;
	int end_y;
	
	end_x = (point.x + 1) * SCALE_M;
	end_y = (point.y + 1) * SCALE_M;
	point.x *= SCALE_M;
	point.y *= SCALE_M;
	while (point.y < end_y)
	{	
		while (point.x < end_x)
		{
			my_pixel_put(all, point.x, point.y, color);
			point.x++;
		}
		point.y++;
		point.x -= SCALE_M;
	} 
}

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

void	ft_cast_ray(t_all *all)
{
	t_plr ray = all->plr;
	double start;
	double end;

	start = all->plr.dir1 - 0.5;
	end = all->plr.dir1 + 0.5;
	int color = 0x7B0099;
	while (start <= end)
	{
		ray = all->plr;
		ray.y *= SCALE_M;
		ray.x *= SCALE_M;
		ray.x += SCALE_M / 2;
		while (all->map[(int)(ray.y / SCALE_M)][(int)(ray.x / SCALE_M)] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);
			my_pixel_put(all, ray.x, ray.y, color);
			//len_r++;
		}
		//draw_line(all, len_r, wall_x, c);
		//len_r = 0;
		//wall_x++;
		start += 1.0 / 10000;
	}
	
}

void draw_player(t_plr *plr, t_all *all)
{
	int end_x;
	int end_y;
	t_plr  p;
	p = *plr;
	end_x = (p.x + 1) * SCALE_M;
	end_y = (p.y + 1) * SCALE_M;
	p.x *= SCALE_M;
	p.y *= SCALE_M;
	ft_cast_ray(all);
	while (p.y < end_y)
	{	
		while (p.x < end_x)
		{
			my_pixel_put(all, p.x , p.y, 0x000099);
			p.x++;
		}
		p.y++;
		p.x -= SCALE_M;
	}
}

t_vec	new_vec(double x, double y)
{
	t_vec res;

	res.x = x;
	res.y = y;
	return (res);
}

t_vec	add_vec(t_vec a, t_vec b)
{
	t_vec res;

	res.x = a.x + b.x;
	res.y = a.x + b.y;
	return (res);
}


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
	//ray_dir = add_vec(all->plr.dir, scalar_mult(camera_x, all->plr.plane));
	ray->ray_dir.x = all->plr.dir.x + all->plr.plane.x * ray->camera_x;
	ray->ray_dir.y = all->plr.dir.y + all->plr.plane.y * ray->camera_x;
	ray->map_p.y = all->plr.y;
	ray->map_p.x = all->plr.x;
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

void	draw_walls(t_all *all)
{
	t_ray	ray;

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
		ray.color = 0xDCDCDC;
		double ratio = 1.0f - 0.2f;
		int r = (int)(ray.color >> 16) * ratio;
		int g = (int)(ray.color >> 8)  * ratio;
		int b = (int)(ray.color & 0xFF) * ratio;
		if (ray.side == 1)
		 	ray.color = r << 16 | g << 8 | b; 
		draw_ver_line(ray.x, ray.draw_start, ray.draw_end, ray.color, all);
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
	if (all->map[(int)(all->plr.y + all->plr.dir.y * MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y += all->plr.dir.y * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->plr.dir.x * MOVE_SPD)] != '1')
		all->plr.x += all->plr.dir.x * MOVE_SPD;
}

void	key_a(t_all *all)
{
	if (all->map[(int)(all->plr.y - all->plr.dir.x * MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y -= all->plr.dir.x * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->plr.dir.y * MOVE_SPD)] != '1')
		all->plr.x += all->plr.dir.y * MOVE_SPD;
}

void	key_s(t_all *all)
{
	if (all->map[(int)(all->plr.y - all->plr.dir.y * MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y -= all->plr.dir.y * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x - all->plr.dir.x * MOVE_SPD)] != '1')
		all->plr.x -= all->plr.dir.x * MOVE_SPD;
}

void	key_d(t_all *all)
{
	if (all->map[(int)(all->plr.y + all->plr.dir.x * MOVE_SPD)][(int)all->plr.x] != '1')
		all->plr.y += all->plr.dir.x * MOVE_SPD;
	if (all->map[(int)(all->plr.y)][(int)(all->plr.x - all->plr.dir.y * MOVE_SPD)] != '1')
		all->plr.x -= all->plr.dir.y * MOVE_SPD;
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
	//ft_putnbr_fd(keycode, 1);
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

void	draw_floor(t_all *all)
{
	t_caf_cast	floor;
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < all->win.win_res.height)
	{
		floor.ray_dir0.x = all->plr.dir.x - all->plr.plane.x;
		floor.ray_dir0.y = all->plr.dir.y - all->plr.plane.y;
		floor.ray_dir1.x = all->plr.dir.x + all->plr.plane.x;
		floor.ray_dir1.y = all->plr.dir.y + all->plr.plane.y;
		floor.p = y - all->win.win_res.height * 0.5;
		floor. pos_z = all->win.win_res.height * 0.5;
		floor.row_dist = floor.pos_z / floor.p;
		floor.step.x = floor.row_dist * (floor.ray_dir1.x - floor.ray_dir0.x) / all->win.win_res.width;
		floor.step.y = floor.row_dist * (floor.ray_dir1.y - floor.ray_dir0.y) / all->win.win_res.width;
		floor.point.x = all->plr.x + floor.row_dist * floor.ray_dir0.x;
		floor.point.y = all->plr.y + floor.row_dist * floor.ray_dir0.y;
		while (x < all->win.win_res.width)
		{
			floor.point.x += floor.step.x;
			my_pixel_put(all, x, y, all->c_floor);
			my_pixel_put(all, x, all->win.win_res.height - y - 1, all->c_celling);
			x++;
		}
		y++;
		x = 0;
	}
}

int exit_m(int keycode)
{
	exit(0);
}
int 	draw_screen(t_all *all)
{
	//int x;
	//int y;
	t_point point;

	//y = 0;
	mlx_clear_window(all->win.mlx, all->win.win);
	check_key_flags(all);
	all->win.img = mlx_new_image(all->win.mlx, all->win.win_res.width, all->win.win_res.height);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bpp, &all->win.line_l, &all->win.en);
	draw_floor(all);
	draw_walls(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	mlx_destroy_image(all->win.mlx, all->win.img);
	return (0);
}

int main(int argc, char *argv[])
{
	t_all all;
	int		fd;
	char	*line;
	t_list	*map;
	char	**tmp;
	int x = 0;
	int y = 0;
	int i;
	int j;
	line = NULL;
	map = NULL;
	t_point point;
	
	all.plr.dir1 = M_PI_2 * 3;
	all.win.mlx = mlx_init();
	all.win.scr_res.height = 2304;
	all.win.scr_res.width = 4096;
	if (argc < 2 && argc > 3)
		error("WRONG NUMBER OF ARGUMENTS!\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error("NO SUCH FILE OR DIRECTORY!\n");
	if (parser(fd, line, &map, &all) < 0)
		error("SOMTHING WRONG WITH .cub FILE!\n");
	all.win.win = mlx_new_window(all.win.mlx, all.win.win_res.width, all.win.win_res.height, "Hello world!");
//rintf("%c\n", all.map[all.plr.y][all.plr.x]);
	key_init(&all);
	printf("f %i c %i\n", all.c_floor, all.c_celling);
	draw_screen(&all);
	mlx_hook(all.win.win, 2, 0, &press_key, &all);
	mlx_hook(all.win.win, 3, 0, &release_key, &all);
	mlx_hook(all.win.win, 17 , 0, &exit_m, &all);
	mlx_loop_hook(all.win.mlx, draw_screen, &all);
	mlx_loop(all.win.mlx);
	
}