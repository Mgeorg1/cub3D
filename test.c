#include "includes/cub3d.h"
#define SCALE_M 5
#define MOVE_SPD 0.2
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

t_vec	sub_vec(t_vec a, t_vec b)
{
	t_vec res;

	res.x = a.x - b.x;
	res.y = a.x - b.y;
	return (res);
}

t_vec	scalar_mult(double a, t_vec b)
{
	t_vec res;
	
	res.x = a * b.x;
	res.y = a * b.y;
	return (res);
}

double	dot_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y);
}

double	len_vec(t_vec a)
{
	return (sqrt(dot_product(a, a)));
}

void	draw_ver_line(int x, int start, int end, int color, t_all *all)
{
	while (start <= end)
	{
		my_pixel_put(all, x, start, color);
		start++;
	}
}

void	draw_walls(t_all *all)
{
	t_vec ray_dir;
	double x;
	double camera_x;
	t_vec side_dist;
	t_point map_p;
	t_vec delta_dist;
	double perp_wall_dist;
	t_point step;
	int hit;
	int side;
	int l_height;
	int draw_start;
	int draw_end;
	int color = 0xFFFF00;

	x = 0;
	while (x < all->win.win_res.width)
	{
		camera_x = 2 * x / (double)(all->win.win_res.width) - 1;
		//ray_dir = add_vec(all->plr.dir, scalar_mult(camera_x, all->plr.plane));
		ray_dir.x = all->plr.dir.x + all->plr.plane.x * camera_x;
		ray_dir.y = all->plr.dir.y + all->plr.plane.y * camera_x;
		map_p.y = all->plr.y;
	 	map_p.x = all->plr.x;
		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);
		hit = 0;
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (all->plr.x - map_p.x) * delta_dist.x;

		}
		else
		{
			step.x = 1;
			side_dist.x = (map_p.x + 1.0 - all->plr.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (all->plr.y - map_p.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map_p.y + 1.0 - all->plr.y) * delta_dist.y;
		}
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map_p.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map_p.y += step.y;
				side = 1;
			}
			if (all->map[map_p.y][map_p.x] == '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_p.x - all->plr.x + (1 - step.x) / 2) / ray_dir.x;
		else
			perp_wall_dist = (map_p.y - all->plr.y + (1 - step.y) / 2) / ray_dir.y;
		
		l_height = (int) (all->win.win_res.height / perp_wall_dist);
		draw_start = -1 * l_height / 2 + all->win.win_res.height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = l_height / 2 + all->win.win_res.height / 2;
		if (draw_end  >= all->win.win_res.height)
			draw_end = all->win.win_res.height - 1;
		color = 0x64B5F6;
		double ratio = 1.0f - 0.2f;
		int r = (int)(color >> 16) * ratio;
		int g = (int)(color >> 8)  * ratio;
		int b = (int)(color & 0xFF) * ratio;
		if (side == 1)
		 	color = r << 16 | g << 8 | b; 
		draw_ver_line(x, draw_start, draw_end, color, all);
		x++;
	}
}
void 	draw_screen(t_all *all)
{
	int x;
	int y;
	t_point point;

	y = 0;
	all->win.img = mlx_new_image(all->win.mlx, all->win.win_res.width, all->win.win_res.height);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bpp, &all->win.line_l, &all->win.en);
	// while(all->map[y])
	// {
	// 	x = 0;
	// 	while (all->map[y][x])
	// 	{
	// 		if (all->map[y][x] == '1')
	// 		{
	// 			point.x = x;
	// 			point.y = y;
	// 			draw_map(all, point, 0xFF0000);
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }
	// draw_player(&all->plr, all);
	draw_walls(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	mlx_destroy_image(all->win.mlx, all->win.img);

}

int press_key(int keycode, t_all *all)
{
	t_vec tmp;
	//ft_putnbr_fd(keycode, 1);
	//ft_putchar_fd(all->map[(int)(all->plr.y)][(int)(all->plr.x)], 1);
	if (keycode == 13)
	{	
		mlx_clear_window(all->win.mlx, all->win.win);
		if (all->map[(int)(all->plr.y + all->plr.dir.y * MOVE_SPD)][(int)all->plr.x] != '1')
			all->plr.y += all->plr.dir.y * MOVE_SPD;
		if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->plr.dir.x * MOVE_SPD)] != '1')
			all->plr.x += all->plr.dir.x * MOVE_SPD;
		draw_screen(all);
	}
	// 0 - a 2 - d s - 1
	if (keycode == 0)
	{
		mlx_clear_window(all->win.mlx, all->win.win);
		if (all->map[(int)(all->plr.y - all->plr.dir.x * MOVE_SPD)][(int)all->plr.x] != '1')
			all->plr.y -= all->plr.dir.x * MOVE_SPD;
		if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->plr.dir.y * MOVE_SPD)] != '1')
			all->plr.x += all->plr.dir.y * MOVE_SPD;
		draw_screen(all);
	}
	if (keycode == 2)
	{
		mlx_clear_window(all->win.mlx, all->win.win);
		if (all->map[(int)(all->plr.y + all->plr.dir.x * MOVE_SPD)][(int)all->plr.x] != '1')
			all->plr.y += all->plr.dir.x * MOVE_SPD;
		if (all->map[(int)(all->plr.y)][(int)(all->plr.x - all->plr.dir.y * MOVE_SPD)] != '1')
			all->plr.x-= all->plr.dir.y * MOVE_SPD;
		//printf("pos1: x = %d y = %d\ndir: x = %f y = %f\n", all->plr.x, all->plr.y, all->plr.dir.x, all->plr.dir.y);
		draw_screen(all);
	}
	if (keycode == 1)
	{
		mlx_clear_window(all->win.mlx, all->win.win);
		if (all->map[(int)(all->plr.y - all->plr.dir.y * MOVE_SPD)][(int)all->plr.x] != '1')
			all->plr.y -= all->plr.dir.y * MOVE_SPD;
		if (all->map[(int)(all->plr.y)][(int)(all->plr.x - all->plr.dir.x * MOVE_SPD)] != '1')
			all->plr.x -= all->plr.dir.x * MOVE_SPD;
		draw_screen(all);
	}
	if (keycode == 123)
	{
		mlx_clear_window(all->win.mlx, all->win.win);
		tmp = all->plr.dir;
		all->plr.dir.x = all->plr.dir.x * cos (-0.1) - all->plr.dir.y * sin(-0.1);
		all->plr.dir.y = tmp.x * sin (-0.1) + all->plr.dir.y * cos(-0.1);
		tmp = all->plr.plane;
		all->plr.plane.x = tmp.x * cos (-0.1) - tmp.y * sin(-0.1);
		all->plr.plane.y = tmp.x * sin(-0.1) + tmp.y * cos(-0.1);
		draw_screen(all);
	}
	if (keycode == 124)
	{
		mlx_clear_window(all->win.mlx, all->win.win);
		tmp = all->plr.dir;
		all->plr.dir.x = all->plr.dir.x * cos (0.1) - all->plr.dir.y * sin(0.1);
		all->plr.dir.y = tmp.x * sin (0.1) + all->plr.dir.y * cos(0.1);
		tmp = all->plr.plane;
		all->plr.plane.x = tmp.x * cos (0.1) - tmp.y * sin(0.1);
		all->plr.plane.y = tmp.x * sin(0.1) + tmp.y * cos(0.1);
		draw_screen(all);
	} //up - 126 down - 125 left - 123 right - 124
	return (0);
}


int exit_m(int keycode)
{
	exit(0);
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
	all.win.scr_res.height = 1080;
	all.win.scr_res.width = 1920;
	if (argc < 2 && argc > 3)
		error("WRONG NUMBER OF ARGUMENTS!\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error("NO SUCH FILE OR DIRECTORY!\n");
	if (parser(fd, line, &map, &all) < 0)
		error("SOMTHING WRONG WITH .cub FILE!\n");
	all.win.win = mlx_new_window(all.win.mlx, all.win.win_res.width, all.win.win_res.height, "Hello world!");
//rintf("%c\n", all.map[all.plr.y][all.plr.x]);
	draw_screen(&all);
	mlx_hook(all.win.win, 2, (1L << 0), &press_key, &all);
	mlx_hook(all.win.win, 17 , 0, &exit_m, &all);
	mlx_loop(all.win.mlx);
	while(1);
}