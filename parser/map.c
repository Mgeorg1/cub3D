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

int		skip_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' && line[i])
		i++;
	return (i);
}

int		check_lnvalid_ch(char *s, t_all *all)
{
	while (*s != 0)
	{
		if (!(*s == 'W' || *s == 'E' || *s == 'S'
		|| *s == 'N' || *s == '1' || *s == '2' || *s == '0'
		|| *s == ' ' || *s == '\n'))
			return (-1);
		if (*s == '2')
			all->sp_num++;
		s++;
	}
	return (0);
}

void	lst_to_matrix(t_all *all, int len)
{
	char	**matrix;
	char	**tmp;
	t_list	*tmp_l;
	int		f;

	all->map_len = len;
	f = 0;
	if (!(matrix = (char **)malloc((len + 1) * sizeof(char *))))
		error("MEMMORY ALLOCATE ERROR!\n", all);
	tmp = matrix;
	tmp_l = all->map_lst;
	while (tmp_l)
	{
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
	ft_lstclear(&all->map_lst, free);
	all->map_lst = NULL;
}

int		make_map(t_all *all)
{
	t_list		*tmp;
	int			len;
	int			f;

	tmp = all->map_lst;
	len = 0;
	f = 0;
	while (tmp)
	{
		check_line(all, f, tmp);
		if (ft_strlen(tmp->content) != 0 || f == 1)
		{
			f = 1;
			len++;
		}
		tmp = tmp->next;
	}
	lst_to_matrix(all, len);
	all->dir_flag = 0;
	malloc_spr(all);
	map_validator(all, 0, 0, 0);
	return (0);
}
