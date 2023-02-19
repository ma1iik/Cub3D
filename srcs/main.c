/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:27:23 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/17 22:24:59 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_direction(t_data *data, char player)
{

	if (player == 'N')
	{
		data->pa = M_PI / 2;
	}
	else if (player == 'E')
	{
		data->pa = 0.00;
	}
	else if (player == 'S')
	{
		data->pa = 3 * M_PI / 2;
	}
	else if (player == 'W')
	{
		data->pa = M_PI;
	}
	// printf("x is %d\ny is %d\n", data->dir.x, data->dir.y);
	get_point_at_distance(data->pl_tx_x, data->pl_tx_y, data->pa, data);
	return ;
}

void find_hit_point(t_data *data, double x1, double y1, double angle)
{
    int map_x, map_y;
    double x2, y2;

    // Finding the map grid cell where the player is located
    map_x = (int)(x1 / TX_L);
    map_y = (int)(y1 / TX_L);

    // Calculating the maximum distance a ray can travel in x and y direction
    double delta_x = sqrt(TX_L * TX_L + (y1 - (map_y * TX_L)) * (y1 - (map_y * TX_L)));
    double delta_y = sqrt(TX_L * TX_L + (x1 - (map_x * TX_L)) * (x1 - (map_x * TX_L)));

    // Initializing the distance traveled in x and y direction
    double dist_x = 0;
    double dist_y = 0;

    // Finding the hit point by incrementing the distance traveled in x and y direction until it hits a wall
    while (data->map[map_y][map_x] == 0)
    {
        if (angle >= 0 && angle < M_PI / 2)
        {
            dist_x += delta_x;
            map_x = (int)((x1 + dist_x * cos(angle)) / TX_L);
        }
        else if (angle >= M_PI / 2 && angle < M_PI)
        {
            dist_x -= delta_x;
            map_x = (int)((x1 + dist_x * cos(angle)) / TX_L);
        }
        else if (angle >= M_PI && angle < 3 * M_PI / 2)
        {
            dist_y -= delta_y;
            map_y = (int)((y1 + dist_y * sin(angle)) / TX_L);
        }
        else
        {
            dist_y += delta_y;
            map_y = (int)((y1 + dist_y * sin(angle)) / TX_L);
        }

        if (map_x < 0 || map_x >= data->map_l || map_y < 0 || map_y >= data->map_h)
            break;
    }

    // Calculating the hit point on the map grid
    x2 = x1 + dist_x * cos(angle);
    y2 = y1 + dist_y * sin(angle);

    // Storing the hit point in the data structure
    data->ray.x = x2;
    data->ray.y = y2;
	my_mlx_pixel_put(data, data->ray.x, data->ray.y, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    return ;
}

int main(int ac, char **av)
{
    t_data *data;

	data = ft_calloc(1, sizeof(t_data));
    if (ft_parsing(ac, data, av[1]) == WRONG)
		return (WRONG);
	init_draw(data);
	//find_hit_point(data, data->pl_tx_x, data->pl_tx_y, data->pa);
	//printf("x=%d  y=%d\n", data->pl_tx_x, data->pl_tx_y);
	//ray_till_wall_v(data);
	//printf("y is --> %d\nx is --> %d\n", data->pl_tx_y, data->pl_tx_x);
	//printf("pl y --> %d\npl tx y / 20 --> %d\n", data->pl_y, (data->pl_tx_y - 100) % 20);
	mlx_hook(data->win, ON_DESTROY, 0, ft_exit, NULL);
	mlx_hook(data->win, ON_KEYDOWN, 1L<<0, ft_action, data);
	mlx_key_hook(data->win, ft_release, data);
	mlx_loop(data->mlx);
    printf ("ALL GOOD\n");
}