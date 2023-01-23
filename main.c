/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:27:23 by ma1iik            #+#    #+#             */
/*   Updated: 2023/01/23 06:19:46 by ma1iik           ###   ########.fr       */
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
		printf("Error : Direction utilized in incorrect manner \n");
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
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E' || line[0] == 'N' || line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue;
		}
		i++;
		free(line);
	}
	i++;
	close(fd);
	return (i);
}

int	ft_fill_map(t_data *data, int fd)
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
		data->map[i++] = ft_strdup(line);
		free (line);
	}
	if (i == 0)
		return (ft_error(3));
	if (ft_fill_map2(data, fd) == WRONG)
		return (WRONG);
	return (RIGHT);
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

int	ft_fill_map2(t_data *data, int fd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (data->map[i][j])
	{
		j = 0;
		tmp = ft_calloc(ft_map_len(data) + 1, sizeof(char));
		if (!tmp)
			return (WRONG);
		tmp[j] = data->map[i][j];
		j++;
		while (j < ft_map_len(data))
			tmp[j++] = '\0';
		free (data->map[i]);
		data->map[i] = tmp;
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
				num++;
			j++;
		}
		i++;
	}
	if (num != 1)
		return (ft_error(5));
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
	if (!data->map)
		return (WRONG);
    fd = open(file, O_RDONLY);
	if (ft_check_ext(data, file) == WRONG)
		return(WRONG);
    if (ft_fill_map(data, fd) == WRONG)
		return (WRONG);
	if (ft_wrongchar(data) == WRONG)
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