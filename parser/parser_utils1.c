/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 22:14:53 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 22:14:54 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_flags(t_all *all)
{
	all->c_flag = 0;
	all->f_flag = 0;
	all->tex.fd_e = NULL;
	all->tex.fd_s = NULL;
	all->tex.fd_n = NULL;
	all->tex.fd_w = NULL;
	all->tex.fd_sprite = NULL;
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

int		matrix_len(char **m)
{
	char **m1;

	m1 = m;
	while (*m1)
		m1++;
	return (m1 - m);
}

void	malloc_spr(t_all *all)
{
	if (!(all->spr = (t_spr*)malloc(all->sp_num * sizeof(t_spr))))
		error("MEMMORY ALLOCATE ERROR!\n", all);
	if (!(all->spr_vis = (t_spr*)malloc(all->sp_num * sizeof(t_spr))))
		error("MEMMORY ALLOCATE ERROR!\n", all);
}

void	check_line(t_all *all, int f, t_list *l)
{
	if (check_lnvalid_ch(l->content, all) < 0)
		error("INVALID CHARACTER IN MAP!\n", all);
	if (ft_strlen(l->content) == 0 && f == 1 && l->next != NULL)
		error("EMPTY LINE IN/AFTER MAP!\n", all);
}
