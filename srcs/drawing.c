/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/03 19:57:02 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_map(char **map, int rows, int cols, t_data *data)
{
    int i, j;
    int x, y;
    int color;

    y = 0;
    for (i = 0; i < rows; i++)
    {
        x = 0;
        for (j = 0; j < cols; j++)
        {
            if (map[i][j] == '1')
                color = 0x444444;
            else if (map[i][j] == '0' || ft_ischar(map[i][j]))
                color = 0xFFFFFF;
			else
				color = 0x000000;
            for (int k = 0; k < 20; k++)
            {
                for (int l = 0; l < 20; l++)
                {
                    my_mlx_pixel_put(data, x + l, y + k, color);
                }
            }
            x += 20;
        }
        y += 20;
    }
}

void	draw_circle(t_data *data, int rad, int x, int y, int color)
{
	int radius = rad;
	for (int i = x + 1 - radius; i <= x - 1 + radius; i++)
	{
		for (int j = y + 1 - radius; j <= y - 1 + radius; j++)
		{
			int distance = (i - x) * (i - x) + (j - y) * (j - y);
			if (distance <= radius * radius)
			{
				my_mlx_pixel_put(data, i, j, color);
			}
		}
	}
}

void draw_char(char **map, int rows, int cols, t_data *data)
{
    int i, j;
    int x, y;

    y = 0;
    for (i = 0; i < rows; i++)
    {
        x = 0;
        for (j = 0; j < cols; j++)
        {
            if (ft_ischar(map[i][j]))
			{
                data->player = map[i][j];
                data->pl_tx_y = y;
                data->pl_tx_x = x;
                ft_direction(data, map[i][j]);
				draw_circle(data, 10, x + 10, y + 10, 0xFF0000);
				return ;
			}
            x += 20;
        }
        y += 20;
    }
}

void get_point_at_distance(float player_x, float player_y, float direction, t_data *data)
{
    data->ray.x = player_x + 50 * cos(direction);
    data->ray.y = player_y + 50 * sin(direction);
}

void init_draw(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	draw_map(data->map, data->map_h, data->map_l, data);
	draw_char(data->map, data->map_h, data->map_l, data);
    my_mlx_pixel_put(data, data->ray.x, data->ray.y, 0xFF0000);
    dda(data, data->ray.x, data->ray.y, 0xFF0000);
    printf("x is %.0f  y is %.0f\n", data->ray.x, data->ray.y);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}