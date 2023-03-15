/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 11:42:49 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_checkways(int x, int y, char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	ft_checkways1(x, y, map, data);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				return (ft_error(6));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_checkwalls(t_data *data)
{
	if (ft_first_last_row(data, data->map_star) == WRONG)
		return (WRONG);
	if (ft_rowsbetween(data, data->map_star) == WRONG)
		return (WRONG);
	if (ft_checkwalls1(data, data->map_star) == WRONG)
		return (WRONG);
	return (RIGHT);
}

int	check_walls2(t_data *data, int y, int x, char **maps)
{
	if (y > 0 && (maps[y - 1][x] == '0'
		|| ft_ischar(maps[y - 1][x])))
		return (ft_error(7));
	if (x <= data->map_l && (maps[y][x + 1] == '0'
		|| ft_ischar(maps[y][x + 1])))
		return (ft_error(7));
	if (y < data->map_h - 1 && (maps[y + 1][x] == '0'
		|| ft_ischar(maps[y + 1][x])))
		return (ft_error(7));
	if (x > 0 && (maps[y][x - 1] == '0'
		|| ft_ischar(maps[y][x - 1])))
		return (ft_error(7));
	return (0);
}

int	ft_checkwalls1(t_data *data, char **maps)
{
	int		x;
	int		y;

	y = 0;
	while (maps[y])
	{
		x = 0;
		while (maps[y][x])
		{
			if (maps[y][x] == '*')
				check_walls2(data, y, x, maps);
			x++;
		}
		y++;
	}
	return (RIGHT);
}

int	ft_first_last_row(t_data *data, char **map)
{
	int	i;

	i = 0;
	while (i < data->map_l)
	{
		if (map[0][i] != '1' && map[0][i] != '*')
		{
			return (ft_error(8));
		}
		i++;
	}
	i = 0;
	while (i < data->map_l)
	{
		if (map[data->map_h - 1][i] != '1' && map[data->map_h - 1][i] != '*')
			return (ft_error(8));
		i++;
	}
	return (RIGHT);
}

int	ft_rowsbetween(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 1;
	while (i < data->map_h - 1)
	{
		j = 0;
		while (map[i][j] == '*')
			j++;
		if (map[i][j] != '1')
			return (ft_error(8));
		j = data->map_l - 1;
		while (map[i][j] == '*')
			j--;
		if (map[i][j] != '1')
			return (ft_error(8));
		i++;
	}
	return (RIGHT);
}
