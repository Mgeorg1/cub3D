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
//# include "../minilibx_mms_20200219/mlx.h"
# include <math.h>

typedef	struct	s_res
{
	int			width;
	int			height;
}				t_res;

typedef struct	s_tex_img
{
	void		*img;
	void		*addr;
	int			bpp;
	int			en;
	int			line;
	int			h;
	int			w;
} 				t_tex_img;

typedef struct	s_textures
{
	char*		fd_n;
	char*		fd_s;
	char*		fd_w;
	char*		fd_e;
	char*		fd_sprite;
	t_tex_img	img_n;
	t_tex_img	img_s;
	t_tex_img	img_e;
	t_tex_img	img_w;
	t_tex_img	img_sp;
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
	t_vec	plane;
}				t_plr;

typedef struct	s_ray
{
	t_vec		ray_dir;
	int			x;
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
	int			tex_num;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	double 		step_tex;
}				t_ray;

typedef struct	s_sp_cast
{
	t_vec	spr_pl;
	double	inv_det;
	t_vec	transf;
	int		sp_h;
	int		sp_screen_x;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	int		sp_w;
	t_point tex;
	int		color;
}				t_sp_cast;

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

typedef	struct	s_spr
{
	t_vec		pos;
	double		dist;
}				t_spr;


typedef struct	s_all
{
	char		*line;
	t_list		*map_lst;
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
	t_textures	textures;
	t_key_flags keys;
	t_spr		*spr;
	int			sp_num;
	t_spr		*spr_vis;
	double		*z_buf;
	int			sp_num_v;
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


void			error(char *s, t_all *all);
int				check_flags(t_all *all);
int 			words_free(char **words, int ret);
int				is_digit_str(char *word);
int				parser(int fd, t_all *all);
int				make_map(t_all *all);
int				atorgb(char *s, t_rgb *color);
int				matrix_len(char **m);
int				rgb_to_int(t_rgb *rgb);
void			free_all(t_all *all);

#endif

