/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 19:27:46 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_col(t_data *data, char *l)
{
	if (ft_strncmp(l, "F", 1) == 0 && ft_isspace(l[1]))
	{
		data->texture.f_n++;
		check_col(data);
		return (1);
	}
	else if (ft_strncmp(l, "C", 1) == 0 && ft_isspace(l[1]))
	{
		data->texture.c_n++;
		check_col(data);
		return (1);
	}
	return (0);
}

int	is_empty(t_data *data, char *l)
{
	int	i;
	int	len;

	i = 0;
	(void)data;
	len = ft_strlen(l);
	if (l[i] == 0)
		return (1);
	while (ft_isspace(l[i]))
		i++;
	if (i == len)
		return (1);
	return (0);
}

void check_col_content(char *col)
{
	int	i;

	i = 0;
	while (col[i])
	{
		if (col[i] != ',' && (!(ft_isdigit(col[i])))
			&& (ft_isspace(col[i]) != 1))
		{
			printf("Error\nInvalid color parameter for floor or celling\n");
			free(col);
			exit(1);
		}
		i++;
	}
}

int	col_range(int r, int g, int b)
{
	if (r < 0 || r > 255)
	{
		printf("Error\nColor value invalid!\n");
		return (0);
	}
	if (g < 0 || g > 255)
	{
		printf("Error\nColor value invalid!\n");
		return (0);
	}
	if (b < 0 || b > 255)
	{
		printf("Error\nColor value invalid!\n");
		return (0);
	}
	return (1);

}

void	col_def_f(char **col_tab, t_data *data)
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
			data->f_r = ft_atoi(col_tab[i]);
		if (i == 1)
			data->f_g = ft_atoi(col_tab[i]);
		if (i == 2)
			data->f_b = ft_atoi(col_tab[i]);
		i++;
	}
	if (!(col_range(data->f_r, data->f_g, data->f_b)))
		exit (1);
}