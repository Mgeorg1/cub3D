/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemustaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:17:21 by aemustaf          #+#    #+#             */
/*   Updated: 2021/01/23 14:17:23 by aemustaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_digit_str(char *word)
{
	int i;

	i = 0;
	while (word[i])
	{
		if (!ft_isdigit(word[i]))
			return (-1);
		i++;
	}
	return	(0);
}

int		rgb_to_int(t_rgb *rgb)
{
	return ((rgb->r << 16) | (rgb->g << 8) | (rgb->b));
}

int		atorgb(char *s, t_rgb *color)
{
	int i;
	char **s1;

	if(!(s1 = ft_split(s, ',')))
		return (-1);
	if (matrix_len(s1) < 3)
		return (words_free(s1, -1));
	i = 0;
	while (i < 3)
	{
		if (is_digit_str(s1[i]))
			return (words_free(s1, -1));
		i++;
	}
	color->r = ft_atoi(s1[0]);
	if (color->r  < 0 && color->r > 255)
		return (words_free(s1, -1));
	color->g = ft_atoi(s1[1]);
	if (color->g  < 0 && color->g > 255)
		return(words_free(s1, -1));
	color->b = ft_atoi(s1[2]);
	if (color->b  < 0 && color->b > 255)
		return (words_free(s1, -1));
	return (words_free(s1, rgb_to_int(color)));
}

int		words_free(char **words, int ret)
{
	int i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	words = NULL;
	return (ret);
}

int		check_flags(t_all *all)
{
	if (!(all->textures.fd_sprite
	&& all->textures.fd_e
	&& all->textures.fd_n
	&& all->textures.fd_s && all->textures.fd_w
	&& all->f_flag && all->c_flag))
		return (-1);
	return (0);
}