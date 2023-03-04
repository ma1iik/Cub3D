/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/04 15:29:19 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_ext(t_data *data, char *file)
{
	int	len;
	int	fd;

	len = ft_strlen(file) - 1;
	(void)data;
	if (!(file[len] == 'b' && file[len - 1] == 'u' && file[len - 2]
			== 'c' && file[len - 3] == '.' && len > 3))
		return (ft_error(1));
	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		return (ft_error(2));
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close (fd);
		return (ft_error(3));
	}
	close(fd);
	return (RIGHT);
}

int	ft_wrongchar(t_data *data)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	num = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'N'
			&& data->map[i][j] != 'S' && data->map[i][j] != 'W'
				&& data->map[i][j] != 'E' && data->map[i][j] != ' ')
				return (ft_error(4));
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->pl_x = j;
				data->pl_y = i;
				num++;
			}
			j++;
		}
		i++;
	}
	if (num != 1)
		return (ft_error(5));
	return (RIGHT);
}

int	ft_checkways1(int x, int y, char **map, t_data *data)
{
	if (x < 0 || x >= data->map_h || y < 0 || y >= data->map_l)
		return (0);
	if (map[x][y] == '1')
		return (0);
	map[x][y] = 'B';
	if (map[x - 1][y] && map[x - 1][y] == '0')
		ft_checkways1(x - 1, y, map, data);
	if (map[x + 1][y] && map[x + 1][y] == '0')
		ft_checkways1(x + 1, y, map, data);
	if (map[x][y - 1] && map[x][y - 1] == '0')
		ft_checkways1(x, y - 1, map, data);
	if (map[x][y + 1] && map[x][y + 1] == '0')
		ft_checkways1(x, y + 1, map, data);
	return (1);
}

int ft_parsing(int ac, t_data *data, char *file)
{
	int		fd;

	if (ac != 2)
	{
		return (ft_error(0));
	}
	data->map = ft_calloc(sizeof(char *), ft_mapsize(file) + 1);
	data->map_star = ft_calloc(sizeof(char *), ft_mapsize(file) + 1);
	data->map_h = ft_mapsize(file);
	//printf("%d\n", data->map_h);
	if (!data->map)
		return (WRONG);
	fd = open(file, O_RDONLY);
	if (ft_check_ext(data, file) == WRONG)
		return (WRONG);
	if (ft_fill_map(data, fd) == WRONG)
		return (WRONG);
	if (ft_wrongchar(data) == WRONG)
		return (WRONG);
	if (ft_checkwalls(data) == WRONG)
		return (WRONG);
	if (ft_checkways(data->pl_y, data->pl_x, data->map_star, data) == WRONG)
		return (WRONG);
	close(fd);
	return (RIGHT);
}
