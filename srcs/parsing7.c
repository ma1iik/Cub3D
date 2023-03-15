/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 19:32:05 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	col_def_c(char **col_tab, t_data *data)
{
	int	i;

	i = 0;
	while (col_tab[i])
		i++;
	if (i != 3)
	{
		printf("Error\nWrong number of color arguments\n");
		exit(1);
	}
	i = 0;
	while (i < 3)
	{
		if (i == 0)
			data->c_r = ft_atoi(col_tab[i]);
		if (i == 1)
			data->c_g = ft_atoi(col_tab[i]);
		if (i == 2)
			data->c_b = ft_atoi(col_tab[i]);
		i++;
	}
	if (!(col_range(data->c_r, data->c_g, data->c_b)))
		exit (1);
}

void	ft_floorc(t_data *data, char *col, char **colors, char *l)
{
	int	i;

	i = 0;
	if ((l[0] == 'F') && (ft_isspace(l[1])))
	{
		check_col_content(col);
		colors = ft_split(col, ',');
		col_def_f(colors, data);
		free(col);
		while (colors[i])
			free(colors[i++]);
		free(colors);
	}
}

void	ft_cellc(t_data *data, char *col, char **colors, char *l)
{
	int	i;

	i = 0;
	if ((l[0] == 'C') && (ft_isspace(l[1])))
	{
		check_col_content(col);
		colors = ft_split(col, ',');
		col_def_c(colors, data);
		free(col);
		while (colors[i])
			free(colors[i++]);
		free(colors);
	}
}

void	col_exst(t_data *data, char *col, char *l)
{
	char	**colors;

	
	colors = NULL;
	ft_floorc(data, col, colors, l);
	ft_cellc(data, col, colors, l);
}

void	do_col(t_data *data, char *l)
{
	int		i;
	char	*col;
	int		len;

	i = 1;
	data->texture.type++;
	len = ft_strlen(l);
	while (ft_isspace(l[i]))
		i++;
	while ((ft_isspace(l[--len])))
		;
	col = ft_substr(l, i, len - i + 1);
	col_exst(data, col, l);
}
