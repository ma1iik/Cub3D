/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/01 04:50:37 by ma1iik           ###   ########.fr       */
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

void init_draw(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	//my_mlx_pixel_put(data, 5, 5, 0x00FF0000);
	draw_map(data->map, data->map_h, data->map_l, data);
	draw_char(data->map, data->map_h, data->map_l, data);
    draw_ray(data, data->pl_tx_x + 10, data->pl_tx_y + 10, data->dir.x, data->dir.y, 0x0000FF);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void draw_ray(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int i = 1;
    int x = x0;
    int y = y0;
    int xinc, yinc;

    if (abs(dx) > abs(dy))
    {
        xinc = dx / abs(dx);
        yinc = dy / abs(dx);
        dy = abs(dy);
    }
    else
    {
        xinc = dx / abs(dy);
        yinc = dy / abs(dy);
        dx = abs(dx);
    }
    while (i <= dx || i <= dy)
    {
        my_mlx_pixel_put(data, x, y, color);
        x += xinc;
        y += yinc;
        i++;
    }
}

void	mlx_line_to(t_data *data, int x, int y, int end_x, int end_y, int color)
{
	int		dx;
	int		dy;
	int		i;
	int		xinc;
	int		yinc;

	dx = end_x - x;
	dy = end_y - y;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	my_mlx_pixel_put(data, x, y, color);
	if (dx > dy)
	{
		int	cumul = dx / 2;
		i = 1;
		while (i <= dx)
		{
			x += xinc;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			my_mlx_pixel_put(data, x, y, color);
			i++;
		}
	}
	else
	{
		int	cumul = dy / 2;
		i = 1;
		while (i <= dy)
		{
			y += yinc;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			my_mlx_pixel_put(data, x, y, color);
			i++;
		}
	}
}

// void draw_ray(t_data *data, int x, int y, int angle, int length)
// {
//     int end_x = x + length * cos(angle);
//     int end_y = y + length * sin(angle);
//     mlx_line_to(data, x, y, end_x, end_y, 0x7FFF8080);
// }
