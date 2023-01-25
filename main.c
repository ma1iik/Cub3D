/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:27:23 by ma1iik            #+#    #+#             */
/*   Updated: 2023/01/25 07:33:19 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

// void mlx_line_put(void *mlx, void *win, int x1, int y1, int x2, int y2, int color)
// {
//     int dx, dy, sx, sy, err, e2;

//     dx = abs(x2 - x1);
//     dy = abs(y2 - y1);
//     sx = x1 < x2 ? 1 : -1;
//     sy = y1 < y2 ? 1 : -1;
//     err = dx - dy;

//     while (1) {
//         mlx_pixel_put(mlx, win, x1, y1, color);
//         if (x1 == x2 && y1 == y2) break;
//         e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x1 += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y1 += sy;
//         }
//     }
// }

int	ft_fill_map(t_data *data, int fd, char **map)
{
    char	*line;
    int		gnl;
	int		i;
	
	gnl = 1;
	i = 0;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C' || line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue;
		}
		map[i++] = ft_strdup(line);
		free (line);
	}
	if (ft_fill_map2(data) == WRONG)
		return (WRONG);
	if (ft_fill_map3(data) == WRONG)
		return (WRONG);
	return (RIGHT);
}

int	ft_fill_map2(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	data->map_l = ft_map_len(data);
	while (data->map[i])
	{
		j = 0;
		tmp = ft_calloc(ft_map_len(data) + 1, sizeof(char));
		if (!tmp)
			return (WRONG);
		while (data->map[i][j])
		{
			tmp[j] = data->map[i][j];
			j++;
		}
		while (j < ft_map_len(data))
			tmp[j++] = ' ';
		tmp[j] = '\0';
		free (data->map[i]);
		data->map[i] = tmp;
		i++;
	}
	return (RIGHT);
}

int	ft_fill_map3(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	data->map_l = ft_map_len(data);
	while (data->map[i])
	{
		j = 0;
		tmp = ft_calloc(ft_map_len(data) + 1, sizeof(char));
		if (!tmp)
			return (WRONG);
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
			{
				tmp[j] = '*';
				j++;
			}
			else
			{
				tmp[j] = data->map[i][j];
				j++;
			}
		}
		tmp[j] = '\0';
		data->map_star[i] = tmp;
		i++;
	}
	return (RIGHT);
}

int ft_check_ext(t_data *data, char *file)
{
	int	len;
	int	fd;

	len = ft_strlen(file) - 1;
	(void)data;
	if(!(file[len] == 'b' && file[len - 1] == 'u' && file[len - 2] == 'c' && file[len - 3] == '.' && len > 3))
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
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0' && data->map[i][j] != 'N'
			&& data->map[i][j] != 'S' && data->map[i][j] != 'W' && data->map[i][j] != 'E' && data->map[i][j] != ' ')
				return(ft_error(4));
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->pl_x = i;
				data->pl_y = j;
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
	if (map[x-1][y] && map[x-1][y] == '0')
    	ft_checkways1(x-1, y, map, data);
	if (map[x+1][y] && map[x+1][y] == '0')
    	ft_checkways1(x+1, y, map, data);
	if (map[x][y-1] && map[x][y-1] == '0')
    	ft_checkways1(x, y-1, map, data);
	if (map[x][y+1] && map[x][y+1] == '0')
    	ft_checkways1(x, y+1, map, data);
	return (1);
}

int	ft_checkways(int x, int y, char **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	ft_checkways1(x, y, map, data);
	while(map[i])
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
	int	i = 0;
	while (data->map_star[i])
		printf("%s\n", data->map_star[i++]);
	if (ft_checkwalls1(data, data->map_star) == WRONG)
		return (WRONG);
	if (ft_first_last_row(data, data->map_star) == WRONG)
		return (WRONG);
	if (ft_rowsbetween(data, data->map_star) == WRONG)
		return (WRONG);
	
	return (RIGHT);
}

int ft_parsing(int ac, t_data *data, char *file)
{
    int     fd;

    if (ac != 2)
	{
		return (ft_error(0));
	}
	data->map = ft_calloc(sizeof(char *), ft_mapsize(file) + 1);
	data->map_star = ft_calloc(sizeof(char *), ft_mapsize(file) + 1);
	data->map_h =  ft_mapsize(file);
	printf("%d\n", data->map_h);
	if (!data->map)
		return (WRONG);
    fd = open(file, O_RDONLY);
	if (ft_check_ext(data, file) == WRONG)
		return(WRONG);
    if (ft_fill_map(data, fd, data->map) == WRONG)
		return (WRONG);
	if (ft_wrongchar(data) == WRONG)
		return (WRONG);
	if (ft_checkwalls(data) == WRONG)
		return (WRONG);
	if (ft_checkways(data->pl_x, data->pl_y, data->map_star, data) == WRONG)
		return (WRONG);
	close(fd);
    return (RIGHT);
}

int main(int ac, char **av)
{
    t_data *data;

	data = ft_calloc(1, sizeof(t_data));
    if (ft_parsing(ac, data, av[1]) == WRONG)
		return (WRONG);
	
    printf ("ALL GOOD\n");
}