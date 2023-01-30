/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:23:53 by ma1iik            #+#    #+#             */
/*   Updated: 2023/01/27 00:13:27 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	ft_error(int n)
{
	if (n == 0)
		printf("Error: Wrong number of arguments\n");
	else if (n == 1)
		printf("Error : Wrong extension of map\n");
	else if (n == 2)
		printf("Error : Map file is a directory\n");
	else if (n == 3)
		printf("Error : Map file not read properly\n");
	if (n == 4)
		printf("Error : Wrong character on map found\n");
	if (n == 5)
		printf("Error : Direction utilized in incorrect manner\n");
	if (n == 6)
		printf("Error : Impossible to enter area found on the map\n");
	if (n == 7)
		printf("Error : Hole in the map\n");
	if (n == 8)
		printf("Error : Wall error\n");
	return (WRONG);
}

int	ft_mapsize(char *file)
{
	int	fd;
	int	i;
	char *line;

	i = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E' || line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue;
		}
		i++;
		free(line);
	}
	i++;
	close(fd);
	return (i - 2);
}


int	ft_map_len(t_data *data)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			j++;
		}
		if (j > len)
			len = j;
		i++;
	}
	return (len);
}

int	ft_ischar(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	else
		return (0);
}

int    ft_checkwalls1(t_data *data, char **maps)
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
            {
                if (y > 0 && (maps[y - 1][x] == '0' || ft_ischar(maps[y - 1][x])))
                    return(ft_error(7));
                if (x <= data->map_l && (maps[y][x + 1] == '0' || ft_ischar(maps[y][x + 1])))
                    return(ft_error(7));
                if (y < data->map_h - 1 && (maps[y + 1][x] == '0' || ft_ischar(maps[y + 1][x])))
                    return(ft_error(7));
                if (x > 0 && (maps[y][x - 1] == '0' || ft_ischar(maps[y][x - 1])))
                    return(ft_error(7));
            }
			x++;
        }
		y++;
    }
	return (RIGHT);
}

int ft_first_last_row(t_data *data, char **map)
{
    int i;

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