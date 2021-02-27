/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 19:34:26 by aemustaf          #+#    #+#             */
/*   Updated: 2021/01/22 19:34:27 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	error(char *s, t_all *all)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	free_all(all);
	exit(EXIT_FAILURE);
}
