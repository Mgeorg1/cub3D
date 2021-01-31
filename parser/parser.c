/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:20:54 by aemustaf          #+#    #+#             */
/*   Updated: 2021/01/22 13:20:55 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#define MIN_WIDTH 160
#define MIN_HEIGHT 160

int		matrix_len(char **m)
{
	char **m1;

	m1 = m;
	while(*m1)
		m1++;
	return (m1 - m);
}

int		parse_res(char **words, t_all *all)
{
	
	if (matrix_len(words) != 3)
		error("WRONG RESOLUTION!\n");
	if (ft_strncmp(words[0], "R", 2))
		error("WRONG RESOLUTION!\n");
	if (is_digit_str(words[1]) == -1 || is_digit_str(words[2]) == -1)
		error("WRONG RESOLUTION!");
	if ((all->win.win_res.width = ft_atoi(words[1])) < 0)
		error("WRONG RESOLUTION!\n");
	if (all->win.scr_res.width < all->win.win_res.width)
		all->win.win_res.width = all->win.scr_res.width;
	if ((all->win.win_res.height = ft_atoi(words[2])) < 0)
		error("WRONG RESOLUTION!\n");
	if (all->win.scr_res.height < all->win.win_res.height)
		all->win.win_res.height = all->win.scr_res.height;
	if (all->win.win_res.height < MIN_HEIGHT
	|| all->win.win_res.width < MIN_WIDTH)
	{
		all->win.win_res.width = MIN_WIDTH;
		all->win.win_res.height = MIN_HEIGHT;
	}
	return (0);
}

int		parse_textures(char **words, t_all *all)
{

	if (matrix_len(words) != 2)
		error("WRONG TEXTURE PATH!\n");
	if ((ft_strncmp(*words, "SO", 3) == 0) && (all->textures.fd_s == NULL)
	&& (open(words[1], O_RDONLY)) > 0)
		all->textures.fd_s = ft_strdup(words[1]);
	else if ((ft_strncmp(*words, "S", 2) == 0) && (all->textures.fd_sprite == NULL)
	&& ((open(words[1], O_RDONLY)) > 0))
		all->textures.fd_sprite = ft_strdup(words[1]);
	else if ((ft_strncmp(*words, "NO", 2) == 0) && (all->textures.fd_n == NULL)
	&& ((open(words[1], O_RDONLY)) > 0))
		all->textures.fd_n = ft_strdup(words[1]);
	else if ((ft_strncmp(*words, "WE", 2) == 0) && (all->textures.fd_w == NULL)
	&& ((open(words[1], O_RDONLY)) > 0))
		all->textures.fd_w = ft_strdup(words[1]);
	else if ((ft_strncmp(*words, "EA", 2) == 0) && (all->textures.fd_e == NULL)
	&& ((open(words[1], O_RDONLY)) > 0))
		all->textures.fd_e = ft_strdup(words[1]);
	else
		error("WRONG TEXTURE PATH!\n");
	return (0);
}


int		parse_color(char **words, t_all *all)
{
	if (matrix_len(words) != 2)
		error("WRONG COLOR!\n");
	if (!ft_strncmp(words[0], "F", 1) && all->f_flag == 0
	&& (all->c_floor = atorgb(words[1], &all->floor)) >= 0)
		all->f_flag = 1;
	else if (!ft_strncmp(words[0], "C", 1) && all->c_flag == 0
	&& (all->c_celling = atorgb(words[1], &all->celling) >= 0))
		all->c_flag = 1;
	else
		error("WRONG COLOR!\n");
	return (0);
}

void	parse_conf(char *line, t_list *map, t_all *all)
{
	char **words;
	int ret;

	if (!(words = ft_split(line, ' ')))
		error("WRONG MEMMORY ALLOCATE!\n");
	else if ('R' == **words)
		ret = parse_res(words, all);
	else if (('S' == **words) || ('N' == **words) || ('W' == **words) || ('E' == **words))
		ret = parse_textures(words, all);
	else if (('F' == **words) || ('C' == **words))
		ret = parse_color(words, all);
	words_free(words, 0);
}

void	init_flags(t_all *all)
{
	all->c_flag = 0;
	all->f_flag = 0;
	all->textures.fd_e = NULL;
	all->textures.fd_s = NULL;
	all->textures.fd_n = NULL;
	all->textures.fd_w = NULL;
	all->textures.fd_sprite = NULL;
}

int		is_onlyspaces(char *s)
{
	while (*s)
	{
		if (*s != ' ')
			return (0);
		s++;
	}
	return (1);
}

int		parser(int fd, char *line, t_list **map, t_all *all)
{
	int	readed_b;
	int i;

	i = 0;
	init_flags(all);
	while ((readed_b = get_next_line(fd, &line)) > 0 && i < 8)
	{
		if (readed_b == -1)
			error("SOMTHING BAD JUST HAPPENDS!\n");
		if (line[0] != '\0' && !is_onlyspaces(line))
		{
			parse_conf(line, *map, all);
			i++;
		}
		free(line);
	}
	if (check_flags(all) < 0)
		error("WRONG NUMBER OF SPECIFICATORS!\n");
	// while (line[0] == 0 && (readed_b = get_next_line(fd, &line)) > 0)
	// {
	// 	if (line[0] == 0)
	// 		free(line);
	// }
	ft_lstadd_back(map, ft_lstnew(line));
	while ((readed_b = get_next_line(fd, &line)) > 0)
	{
		if (readed_b == -1)
			error("SOMTHING WRONG WITH '.cub' FILE!\n");
		ft_lstadd_back(map, ft_lstnew(line));
	}
	ft_lstadd_back(map, ft_lstnew(line));
	make_map(all, *map);
	return (0);
}