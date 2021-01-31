/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:56:37 by aemustaf          #+#    #+#             */
/*   Updated: 2021/01/23 15:56:40 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>
#include <string.h>


int		skip_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' && line[i])
		i++;
	return (i);
}

int		check_lnvalid_ch(char *s)
{
	while(*s != 0)
	{
		if (!(*s == 'W' || *s == 'E' || *s == 'S' 
		|| *s == 'N' || *s == '1' || *s == '2' || *s == '0' || *s == ' ' || *s == '\n'))
			return (-1);
		s++;
	}
	return (0);
}


// void	init_map(t_map_info *line, t_all *all)
// {
// 	if (!all->map)
// 		return(-1);
// 	line->previus_line = NULL;
// 	line->dir_flag = 0;
// }

void lst_to_matrix(t_list *map, t_all *all, int len)
{
	char **matrix;
	char **tmp;
	t_list *tmp_l;
	int f;

	all->map_len = len;
	f = 0;
	if (!(matrix = (char **)malloc((len + 1) * sizeof(char *))))
		error("MEMMORY ALLOCATE ERROR!\n");
	tmp = matrix;
	tmp_l = map;
	while (tmp_l)
	{
		//ft_putendl_fd(map->content, 1);
		if (ft_strlen(tmp_l->content) || f == 1)
		{
			*matrix = ft_strdup(tmp_l->content);
			matrix++;
			f = 1;
		}
		tmp_l = tmp_l->next;
	}
	all->map = tmp;
	*matrix = NULL;
	ft_lstclear(&map, free);
}

void	line_validator(t_all *all, int x, int y)
{
	//printf("%s\n%c, %i, %i ", all->map[y], all->map[y][x], x, y);
	if (all->dir_flag > 1)
		error("THE PLAYER DIRECTION MUST BE ONE!\n");
	if (x > 0 && (y + 1) < all->map_len && (x + 1) < ft_strlen(all->map[y]) && y > 0)
	{
		if (x >= ft_strlen(all->map[y + 1]) || x >= ft_strlen(all->map[y - 1]))
			error("THE MAP IS NOT CLOSED!\n");
		if (all->map[y][x - 1]  == ' ' || all->map[y][x + 1] == ' '
		|| all->map[y - 1][x] == ' ' || all->map[y + 1][x] == ' ' || all->map[y - 1][x - 1] == ' '
		|| all->map[y - 1][x + 1] == ' ' || all->map[y + 1][x - 1] == ' ' || all->map[y + 1][x + 1] == ' '
		|| all->map[y + 1][x + 1] == '\0' || all->map[y - 1][x + 1] == '\0')
			error("THE MAP IS NOT CLOSED!\n");
	}
	else
		error("THE MAP IS NOT CLOSED!\n");
}

void	get_start_dir(t_all *all, char c, int x, int y)
{
	all->plr.x = x;
	all->plr.y = y;
	all->dir_flag++;
	if (c == 'E')
	{
		all->plr.dir.x = 1;
		all->plr.dir.y = 0;
		all->plr.plane.x = 0;
		all->plr.plane.y = -0.66;
	}
	if (c == 'W')
	{
		all->plr.dir.x = -1;
		all->plr.dir.y = 0;
		all->plr.plane.x = 0;
		all->plr.plane.y = -0.66;
	}
	if (c == 'N')
	{
		all->plr.dir.x = 0;
		all->plr.dir.y = -1;
		all->plr.plane.x = 0.66;
		all->plr.plane.y = 0;
	}
	if (c == 'S')
	{
		all->plr.dir.x = 0;
		all->plr.dir.y = 1;
		all->plr.plane.x = -0.66;
		all->plr.plane.y = 0;
	}
}

void	map_validator(t_all *all)
{
	int		y;
	int 	x;

	y = 0;
	while (all->map[y])
	{
		x = 0;
		while(all->map[y][x])
		{
			if (all->map[y][x] == ' ' || all->map[y][x] =='1')	
				x++;
			if (all->map[y][x] == '0' || all->map[y][x] == 'N' || all->map[y][x] == 'S'
			|| all->map[y][x] == 'W' ||  all->map[y][x] == 'E' || all->map[y][x] == '2')
			{
				if (all->map[y][x] == 'N' || all->map[y][x] == 'S' || all->map[y][x] == 'W' ||  all->map[y][x] == 'E')
					get_start_dir(all, all->map[y][x], x, y);
				line_validator(all, x, y);
				x++;
			}
		}
		y++;
	}
	if (all->dir_flag == 0)
		error("THE PLAYER DIRECTION MUST BE ONE!\n");
}


int		make_map(t_all *all, t_list *map)
{
	t_list		*tmp;
	int			len;
	int			f;

	tmp = map;
	len = 0;
	f = 0;
	while (tmp)
	{
		if (check_lnvalid_ch(tmp->content) < 0)
			error("INVALID CHARACTER IN MAP!\n");
		if (ft_strlen(tmp->content) != 0 || f == 1)
		{
			f = 1;
			len++;
		}
		tmp = tmp->next;
	}
	lst_to_matrix(map, all, len);
	all->dir_flag = 0;
	map_validator(all);
	return (0);
}
