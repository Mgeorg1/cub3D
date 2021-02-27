/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 00:21:05 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/26 00:21:08 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_isspace(const char *str)
{
	if (*str == ' ' || *str == '\t' || *str == '\r'
			|| *str == '\n' || *str == '\v' || *str == '\f')
		return (1);
	return (0);
}

int			my_atoi(const char *str)
{
	long long	i;
	long long	b;

	b = 214748364;
	i = 0;
	while (ft_isspace(str) == 1)
		str++;
	if (ft_strncmp(str, "0", 2) == 0)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if ((i > b) || (i == b && (*str - '0') >= 7))
			return (2147483647);
		i = i * 10 + *str - 48;
		str++;
	}
	return (i);
}

void		check_res(t_all *all)
{
	if ((all->win.scr_res.w < all->win.w_res.w
	|| all->win.scr_res.h < all->win.w_res.h) && all->save_f == 0)
	{
		all->win.w_res.w = all->win.scr_res.w;
		all->win.w_res.h = all->win.scr_res.h;
	}
	if (all->win.scr_res.w < all->win.w_res.w && all->save_f == 1)
		all->win.w_res.w = MAX_R_W;
	if (all->win.scr_res.h < all->win.w_res.h && all->save_f == 1)
		all->win.w_res.h = MAX_R_H;
	if (all->win.w_res.h < MIN_HEIGHT
	|| all->win.w_res.w < MIN_WIDTH)
	{
		all->win.w_res.w = MIN_WIDTH;
		all->win.w_res.h = MIN_HEIGHT;
	}
}
