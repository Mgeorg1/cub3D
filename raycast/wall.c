/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:14:07 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 20:14:09 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		ray_init(t_all *all, t_ray *ray)
{
	ray->camera_x = 2 * ray->x / (double)(all->win.w_res.w) - 1;
	ray->ray_dir.x = all->plr.dir.x + all->plr.pln.x * ray->camera_x;
	ray->ray_dir.y = all->plr.dir.y + all->plr.pln.y * ray->camera_x;
	ray->map_p.y = (int)all->plr.y;
	ray->map_p.x = (int)all->plr.x;
	if (ray->ray_dir.x == 0 && ray->ray_dir.y == 0)
		ray->delta_dist.x = 0;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0 && ray->ray_dir.x == 0)
		ray->delta_dist.y = 0;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	ray->hit = 0;
}

void		cell_intersects_calc(t_all *all, t_ray *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (all->plr.x - r->map_p.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map_p.x + 1.0 - all->plr.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (all->plr.y - r->map_p.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map_p.y + 1.0 - all->plr.y) * r->delta_dist.y;
	}
}

void		dda(t_all *all, t_ray *ray)
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
		ray->wall_d = (ray->map_p.x - all->plr.x + (1 - ray->step.x) / 2)
		/ ray->ray_dir.x;
	else
		ray->wall_d = (ray->map_p.y - all->plr.y + (1 - ray->step.y) / 2)
		/ ray->ray_dir.y;
}

t_tex_img	*wall_calc(t_all *all, t_ray *r, t_tex_img *t)
{
	r->l_height = (int)((all->win.w_res.w * OPT_RATIO / r->wall_d));
	r->draw_start = -1 * r->l_height / 2 + all->win.w_res.h / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->l_height / 2 + all->win.w_res.h / 2;
	if (r->draw_end >= all->win.w_res.h)
		r->draw_end = all->win.w_res.h - 1;
	if (r->side == 0)
		r->wall_x = all->plr.y + r->wall_d * r->ray_dir.y;
	else
		r->wall_x = all->plr.x + r->wall_d * r->ray_dir.x;
	t = get_side(r, all);
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)t->w);
	if (r->side == 0 && r->ray_dir.x > 0)
		r->tex_x = t->w - r->tex_x - 1;
	else if (r->side == 1 && r->ray_dir.y < 0)
		r->tex_x = t->w - r->tex_x - 1;
	r->step_tx = 1.0 * t->w / r->l_height;
	r->tex_pos = (r->draw_start - all->win.w_res.h / 2 + r->l_height / 2)
	* r->step_tx;
	return (t);
}

void		draw_walls(t_all *all)
{
	t_ray		ray;
	t_tex_img	*t;

	ray.x = 0;
	while (ray.x < all->win.w_res.w)
	{
		ray_init(all, &ray);
		dda(all, &ray);
		t = wall_calc(all, &ray, t);
		draw_floor(ray.x, ray.draw_end, all->c_floor, all);
		draw_celling(ray.x, ray.draw_start, all->c_celling, all);
		while (ray.draw_start <= ray.draw_end)
		{
			ray.tex_y = (int)ray.tex_pos & (t->h - 1);
			ray.tex_pos += ray.step_tx;
			ray.color = get_color(t, ray.tex_x, ray.tex_y);
			my_pixel_put(all, ray.x, ray.draw_start, ray.color);
			ray.draw_start++;
		}
		all->z_buf[ray.x] = ray.wall_d;
		ray.x++;
	}
}
