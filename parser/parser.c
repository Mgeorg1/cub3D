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

int		parse_res(char **words, t_all *all)
{
	if (matrix_len(words) != 3)
		error("WRONG RESOLUTION!\n", all);
	if (ft_strncmp(words[0], "R", 2))
		error("WRONG RESOLUTION!\n", all);
	if (is_digit_str(words[1]) == -1 || is_digit_str(words[2]) == -1)
		error("WRONG RESOLUTION!", all);
	if ((all->win.w_res.w = my_atoi(words[1])) < 0)
		error("WRONG RESOLUTION!\n", all);
	if ((all->win.w_res.h = my_atoi(words[2])) < 0)
		error("WRONG RESOLUTION!\n", all);
	check_res(all);
	return (0);
}

int		parse_textures(char **words, t_all *all)
{
	if (matrix_len(words) != 2)
		error("WRONG TEXTURE PATH!\n", all);
	if ((ft_strncmp(*words, "SO", 3) == 0) && (all->tex.fd_s == NULL)
	&& (open(words[1], O_RDONLY)) > 0)
		all->tex.fd_s = ft_strdup(words[1]);
	else if ((ft_strncmp(*words, "S", 2) == 0) && (all->tex.fd_sprite == NULL)
	&& ((open(words[1], O_RDONLY)) > 0))
		all->tex.fd_sprite = ft_strdup(words[1]);
	else if ((ft_strncmp(*words, "NO", 2) == 0) && (all->tex.fd_n == NULL)
	&& ((open(words[1], O_RDONLY)) > 0))
		all->tex.fd_n = ft_strdup(words[1]);
	else if ((ft_strncmp(*words, "WE", 2) == 0) && (all->tex.fd_w == NULL)
	&& ((open(words[1], O_RDONLY)) > 0))
		all->tex.fd_w = ft_strdup(words[1]);
	else if ((ft_strncmp(*words, "EA", 2) == 0) && (all->tex.fd_e == NULL)
	&& ((open(words[1], O_RDONLY)) > 0))
		all->tex.fd_e = ft_strdup(words[1]);
	else
		error("WRONG TEXTURE PATH!\n", all);
	return (0);
}

int		parse_color(char **words, t_all *all)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if (matrix_len(words) != 2)
		error("WRONG COLOR!\n", all);
	while (words[1][i])
	{
		if (words[1][i] == ',')
			k++;
		i++;
	}
	if (k != 2)
		error("WRONG COLOR!\n", all);
	if (!ft_strncmp(words[0], "F", 2) && all->f_flag == 0
	&& (all->c_floor = atorgb(words[1], &all->floor)) >= 0)
		all->f_flag = 1;
	else if (!ft_strncmp(words[0], "C", 2) && all->c_flag == 0
	&& (all->c_celling = atorgb(words[1], &all->celling)) >= 0)
		all->c_flag = 1;
	else
		error("WRONG COLOR!\n", all);
	return (0);
}

void	parse_conf(char *line, t_all *all)
{
	char	**words;
	int		ret;

	if (!(words = ft_split(line, ' ')))
		error("WRONG MEMMORY ALLOCATE!\n", all);
	else if ('R' == **words)
		ret = parse_res(words, all);
	else if (('S' == **words) || ('N' == **words)
	|| ('W' == **words) || ('E' == **words))
		ret = parse_textures(words, all);
	else if (('F' == **words) || ('C' == **words))
		ret = parse_color(words, all);
	words_free(words, 0);
}

void	parser(int fd, t_all *all)
{
	int	readed_b;
	int i;

	i = 0;
	init_flags(all);
	while ((readed_b = get_next_line(fd, &all->line)) > 0 && i < 8)
	{
		if (all->line[0] != '\0' && !is_onlyspaces(all->line))
		{
			parse_conf(all->line, all);
			i++;
		}
		free(all->line);
	}
	if (readed_b == -1)
		error("SOMTHING BAD JUST HAPPENDS!\n", all);
	check_flags(all);
	ft_lstadd_back(&all->map_lst, ft_lstnew(all->line));
	while ((readed_b = get_next_line(fd, &all->line)) > 0)
		ft_lstadd_back(&all->map_lst, ft_lstnew(all->line));
	if (readed_b == -1)
		error("SOMTHING WRONG WITH '.cub' FILE!\n", all);
	ft_lstadd_back(&all->map_lst, ft_lstnew(all->line));
	make_map(all);
}
