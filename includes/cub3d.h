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
# define SCALE_M 5
# define MOVE_SPD 0.07
# define VIEW_DIST 4000.0
# define MAX_R_W 15000
# define MAX_R_H 8438

typedef	struct	s_res
{
	int			w;
	int			h;
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
	t_res		w_res;
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
	t_vec	pln;
}				t_plr;

typedef struct	s_ray
{
	t_vec		ray_dir;
	int			x;
	double		camera_x;
	t_vec		side_dist;
	t_point		map_p;
	t_vec		delta_dist;
	double		wall_d;
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
	double 		step_tx;
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
	int		d;
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
	t_textures	tex;
	t_key_flags keys;
	t_spr		*spr;
	int			sp_num;
	t_spr		*spr_vis;
	double		*z_buf;
	int			sp_num_v;
	int			save_f;
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
void			check_flags(t_all *all);
int 			words_free(char **words, int ret);
int				is_digit_str(char *word);
void			parser(int fd, t_all *all);
int				make_map(t_all *all);
int				atorgb(char *s, t_rgb *color);
int				matrix_len(char **m);
int				rgb_to_int(t_rgb *rgb);
void			free_all(t_all *all);
void			make_bmp(t_all *all);
int 			draw_screen(t_all *all);
void			draw_walls(t_all *all);
void			my_pixel_put(t_all *all, int x, int y, int color);
int				get_color(t_tex_img *img, int x, int y);
void			check_key_flags(t_all *all);
void			draw_sprites(t_all *all);
void			my_pixel_put(t_all *all, int x, int y, int color);
int				get_color(t_tex_img *img, int x, int y);
void			draw_floor(int x, int end, int c, t_all *all);
void			draw_celling(int x, int start, int c, t_all *all);
t_tex_img		*get_side(t_ray *ray, t_all *all);
void			init_textures(t_textures *t, void *mlx, t_all *all);
void			key_init(t_all *all);
void			key_w(t_all *all);
void			key_a(t_all *all);
void			key_s(t_all *all);
void			key_d(t_all *all);
void			key_left(t_all *all);
void			key_right(t_all *all);
int				press_key(int keycode, t_all *all);
int				release_key(int keycode, t_all *all);
int 			exit_m(t_all *all);
void			draw_sprites(t_all *all);
void			swap_sp(t_spr *x, int j, int i);
int				matrix_len(char **m);
int				is_onlyspaces(char *s);
void			init_flags(t_all *all);
void			malloc_spr(t_all *all);
void			check_line(t_all *all, int f, t_list *l);
int				check_lnvalid_ch(char *s, t_all *all);
void			map_validator(t_all *all, int x, int y, int sp_count);
int				my_atoi(const char *str);
#endif

