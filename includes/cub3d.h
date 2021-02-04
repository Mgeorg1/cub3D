/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:54:31 by aemustaf          #+#    #+#             */
/*   Updated: 2021/01/22 12:54:33 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../minilibx_opengl_20191021/mlx.h"
#include <math.h>

typedef	struct	s_res
{
	int			width;
	int			height;
}				t_res;

typedef struct	s_textures
{
	char*		fd_n;
	char*		fd_s;
	char*		fd_w;
	char*		fd_e;
	char*		fd_sprite;
}				t_textures;

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	t_res		win_res;
	t_res		scr_res;
	void		*img;
	void		*addr;
	int			bpp;
	int			en;
	int			line_l;
}				t_win;

typedef struct 	s_point
{
	int		x;
	int		y;
}				t_point;


typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_vec
{
	double x;
	double y;
}				t_vec;


typedef struct	s_plr
{
	double		x;
	double		y;
	t_vec 	dir;
	double	dir1;
	double	start;
	double	end;
	t_vec	plane;
}				t_plr;

typedef struct	s_ray
{
	t_vec		ray_dir;
	double		x;
	double		camera_x;
	t_vec		side_dist;
	t_point		map_p;
	t_vec		delta_dist;
	double		perp_wall_dist;
	t_point		step;
	int			hit;
	int			side;
	int			l_height;
	int			draw_start;
	int			draw_end;
	int			color;
}				t_ray;

typedef struct	s_caf_cast
{
	t_vec		ray_dir0;
	t_vec		ray_dir1;
	double		pos_z;
	int			p;
	double		row_dist;
	t_vec		point;
	t_point		cell;
	t_vec		step;
}				t_caf_cast;

typedef struct	s_key_flags
{
	int			w;
	int 		a;
	int			s;
	int			d;
	int			left_arrow;
	int			right_arrow;
}				t_key_flags;

typedef struct	s_all
{
	t_win		win;
	t_plr		plr;
	char 		**map;
	int			map_len;
	t_rgb		celling;
	t_rgb 		floor;
	int			c_celling;
	int			c_floor;
	int			c_flag;
	int			f_flag;
	int			dir_flag;
	t_textures textures;
	t_key_flags keys;
}				t_all;

// typedef struct	s_map_info
// {
// 	char    *line;
// 	char	*previus_line;
// 	char	*next_line;
// 	int		prev_len;
// 	int		next_len;
// 	int		dir_flag;
// }				t_map_info;


void			error(char *s);
int				check_flags(t_all *all);
int 			words_free(char **words, int ret);
int				is_digit_str(char *word);
int				parser(int fd, char *line, t_list **map, t_all *all);
int				make_map(t_all *all, t_list *map);
int				atorgb(char *s, t_rgb *color);
int				matrix_len(char **m);
int				rgb_to_int(t_rgb *rgb);

#endif

