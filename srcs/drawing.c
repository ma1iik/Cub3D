/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/06 09:46:12 by ma1iik           ###   ########.fr       */
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
            for (int k = 0; k < TX_L; k++)
            {
                for (int l = 0; l < TX_L; l++)
                {
                    my_mlx_pixel_put(data, x + l, y + k, color);
                }
            }
            x += TX_L;
        }
        y += TX_L;
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
				draw_circle(data,  TX_L/2, x + TX_L/2, y + TX_L/2, 0xFF0000);
				return ;
			}
            x += TX_L;
        }
        y += TX_L;
    }
}

void get_point_at_distance(float player_x, float player_y, float direction, t_data *data)
{
    data->ray.x = player_x + 50 * cos(direction);
    data->ray.y = player_y + 50 * sin(direction);
}

void ray_till_wall(t_data *data)
{
    int     r;
    float rx;
    float ry;
    float xo;
    float yo;
    int dof;
    float atan;
    int mx;
    int my;
    
    r = 0;
    while (r++ < 1)
    {
        dof = 0;
        atan = -1 / tan(data->pa);
        if (data->pa < M_PI)
        {
            printf("looking down\n");
            ry = (int)((((round(data->pl_tx_y) / TX_L)) * TX_L) + TX_L);
            // ry = (int)((((round(data->pl_tx_y) / TX_L)) * TX_L));
            rx = ((data->pl_tx_y + TX_L/2) - ry) * atan + data->pl_tx_x + TX_L/2;
            printf("starting rx[%.0f]ry[%.0f]\n", rx, ry);
            yo = TX_L;
            xo = - yo * atan;
        }
        else if (data->pa > M_PI)
        {
            printf("looking up\n");
            ry = (int)((((round(data->pl_tx_y - TX_L) / TX_L)) * TX_L) + TX_L);
            rx = ((data->pl_tx_y + TX_L/2) - ry) * atan + data->pl_tx_x + TX_L/2;
            printf("starting rx[%.0f]ry[%.0f]\n", rx, ry);
            //my_mlx_pixel_put(data, rx, ry, 0xFF0000);
             yo = -TX_L;
             xo = - yo * atan;
        }
        else if (data->pa == 0 || data->pa == M_PI)
        {
            printf("looking straight\n");
            rx = data->pl_tx_x;
            ry = data->pl_tx_y;
            dof = 30;
        }
        while (rx >= 0 && rx < data->map_l * TX_L && ry >= 0 && ry < data->map_h * TX_L)
        {
            //printf("entered\n");
           // printf("mapl %d map h %d\n", data->map_l, data->map_h);
            mx = (int) ceilf(rx / TX_L) - 1;
            my = (int) ceilf(ry / TX_L) - 1;
            if (mx < 0 || mx >= data->map_l || my < 0 || my >= data->map_h)
                break;
            if (data->map[my][mx] && data->map[my][mx] == '1')
            {
                dof = 30;
                if(data->pa > 0 && data->pa < M_PI)
                    ry -= TX_L;
                printf("walls found at mx[%d]my[%d]\n", mx, my);
                printf("walls found at rx[%.0f]ry[%.0f]\n", rx, ry);
                break ;
            }
            else
            {
                if (rx + xo < 0 )
                {
                    printf("here1\n");
                    rx = 0;
                }
                else if (rx + xo > data->map_l * TX_L)
                {
                    printf("here2\n");
                    rx = data->map_l * TX_L;
                }
                else
                    rx += xo;
                if (ry + yo < 0)
                {
                    printf("here3\n");
                    ry = 0;
                }
                else if (ry+ yo > data->map_h * TX_L)
                {
                    printf("here4\n");
                    ry = data->map_h * TX_L;
                }
                else
                    ry += yo;
                dof++;
            }
        }
       // printf("mx[%d]my[%d]\n", mx * TX_L - 10, my * TX_L);
        // printf("mx[%d]my[%d]\n", mx, my);
        printf("rx[%.0f]ry[%.0f]\n", rx, ry);
        printf("pa is %.2f\n\n", data->pa);
        dda(data, rx, ry, 0xFF0000);
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    }
}

void init_draw(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	draw_map(data->map, data->map_h, data->map_l, data);
	draw_char(data->map, data->map_h, data->map_l, data);
    //my_mlx_pixel_put(data, data->ray.x, data->ray.y, 0xFF0000);
    //dda(data, data->ray.x, data->ray.y, 0xFF0000);
    ray_till_wall(data);
    //printf("x is %.0f  y is %.0f\n", data->ray.x, data->ray.y);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}