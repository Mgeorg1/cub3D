/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:33:04 by aemustaf          #+#    #+#             */
/*   Updated: 2021/02/21 21:33:05 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		press_key(int keycode, t_all *all)
{
	if (keycode == 13)
		all->keys.w = 1;
	if (keycode == 0)
		all->keys.a = 1;
	if (keycode == 2)
		all->keys.d = 1;
	if (keycode == 1)
		all->keys.s = 1;
	if (keycode == 123)
		all->keys.left_arrow = 1;
	if (keycode == 124)
		all->keys.right_arrow = 1;
	if (keycode == 53)
		exit_m(all);
	return (0);
}

int		release_key(int keycode, t_all *all)
{
	if (keycode == 13)
		all->keys.w = 0;
	if (keycode == 0)
		all->keys.a = 0;
	if (keycode == 2)
		all->keys.d = 0;
	if (keycode == 1)
		all->keys.s = 0;
	if (keycode == 123)
		all->keys.left_arrow = 0;
	if (keycode == 124)
		all->keys.right_arrow = 0;
	return (0);
}


void	check_key_flags(t_all *all)
{
	if (all->keys.w == 1)
		key_w(all);
	if (all->keys.a == 1)
		key_a(all);
	if (all->keys.s == 1)
		key_s(all);
	if (all->keys.d == 1)
		key_d(all);
	if (all->keys.left_arrow == 1)
		key_left(all);
	if (all->keys.right_arrow == 1)
		key_right(all);
}

void	key_init(t_all *all)
{
	all->keys.w = 0;
	all->keys.a = 0;
	all->keys.s = 0;
	all->keys.d = 0;
	all->keys.left_arrow = 0;
	all->keys.right_arrow = 0;
}
