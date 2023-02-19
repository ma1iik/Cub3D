/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:34:17 by ma1iik            #+#    #+#             */
/*   Updated: 2023/02/19 04:34:58 by ma1iik           ###   ########.fr       */
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
                data->pl_tx_y = y + TX_L/2;
                data->pl_tx_x = x + TX_L/2;
                ft_direction(data, map[i][j]);
				draw_circle(data,  TX_L/2, x + TX_L/2, y + TX_L/2, 0xFF0000);
				return ;
			}
            x += TX_L;
        }
        y += TX_L;
    }
}

void get_point_at_distance(double player_x, double player_y, double direction, t_data *data)
{
    data->ray.x = player_x + 50 * cos(direction);
    data->ray.y = player_y + 50 * sin(direction);
}

void ray_till_wall_h(t_data *data)
{
    int     r;
    double rx;
    double ry;
    double xo;
    double yo;
    int mx;
    int my;
    
    r = 0;
    while (r++ < 1)
    {
        if (data->pa < 0.00 + 0.01 && data->pa > 0.00 - 0.01)
        {
            printf("looking straight\n");
            rx = data->map_l * TX_L;
            ry = data->pl_tx_y;
            return;
        }
        else if(data->pa < M_PI + 0.01 && data->pa > M_PI - 0.01)
        {
             printf("looking straight\n");
            rx = 0;
            ry = data->pl_tx_y;
            return;
        }
        else if (data->pa > M_PI && data->pa < 2 * M_PI)
        {
            printf("looking down\n");
            ry = floor(data->pl_tx_y/TX_L) * (TX_L) + TX_L;
            rx =  data->pl_tx_x + (data->pl_tx_y-ry)/tan((data->pa));
            printf("starting rx[%.0f]ry[%.0f]\n", rx, ry);
            yo = TX_L;
            xo = - yo/tan(data->pa);
        }
        else if (data->pa < M_PI && data->pa > 0)
        {
            printf("looking up\n");
            ry = floor(data->pl_tx_y/TX_L) * (TX_L) - 0.0001;
            rx =  data->pl_tx_x + (data->pl_tx_y-ry)/tan((data->pa));
            printf("starting rx[%.0f]ry[%.0f]\n", rx, ry);
            yo = -TX_L;
            xo = - yo /tan(data->pa);
        }
        printf("pa is %.2f\n", data->pa);
        while (rx > 0 && rx < data->map_l * TX_L && ry > 0 && ry < data->map_h * TX_L)
        {
            mx = (int) floor(rx / TX_L);
            my = (int) floor(ry / TX_L);
            // printf("mxy at x[%d] y[%d]\n", mx, my);
            // printf("rxy at x[%.2f] y[%.2f]\n", rx, ry);
            if ((mx < 0 || mx >= data->map_l || my < 0 || my >= data->map_h) || (data->map[my][mx] && data->map[my][mx] == '1'))
                break;
            // printf("entered\n");
                if (rx + xo < 0 )
                    rx = 0;
                else if (rx + xo > data->map_l * TX_L)
                    rx = data->map_l * TX_L;
                else
                    rx += xo;
                if (ry + yo < 0)
                    ry = 0;
                else if (ry+ yo > data->map_h * TX_L)
                    ry = data->map_h * TX_L;
                else
                    ry += yo;
        }
        printf("walls found at mx[%d]my[%d]\n", mx, my);
        printf("walls found at rx[%.0f]ry[%.0f]\n", rx, ry);
        dda(data, rx, ry, 0xFF0000);
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    }
}

void ray_till_wall_v(t_data *data)
{
    int     r;
    double rx;
    double ry;
    double xo;
    double yo;
    int mx;
    int my;
    
    r = 0;
    while (r++ < 1)
    {
        printf("pa is %.2f\n", data->pa);
        if (data->pa > M_PI/2 - 0.01 && data->pa < M_PI/2 + 0.01)
        {
            rx = data->pl_tx_x;
            ry = 0;
            return;
        }
        else if(data->pa >  3*M_PI/2 - 0.01 && data->pa <  3*M_PI/2 + 0.01)
        {
            rx = data->pl_tx_x;
            ry = data->map_h * TX_L;
            return;
        }
        else if ((data->pa >= 0 && data->pa <= M_PI/2) || (data->pa > 3 * M_PI / 2 && data->pa <= 2 * M_PI))
        {
            printf("looking right\n");
            rx =  floor(data->pl_tx_x/TX_L) * TX_L + TX_L;
            ry = data->pl_tx_y + (data->pl_tx_x - rx)*tan(data->pa);
            printf("starting rx[%.0f]ry[%.0f]\n", rx, ry);
            yo =  -TX_L * tan(data->pa);
            xo = TX_L;
        }
        else if (data->pa > M_PI/2 && data->pa < 3*M_PI/2)
        {
            printf("looking left\n");
            rx =  floor(data->pl_tx_x/TX_L) * TX_L - 0.0001;
            ry = data->pl_tx_y + (data->pl_tx_x - rx)*tan(data->pa);
            printf("starting rx[%.0f]ry[%.0f]\n", rx, ry);
            yo = TX_L * tan(data->pa);
            xo = -TX_L;
        }
        //printf("yo  is %.2fxo is %.2f\n", yo, xo);
        while (rx > 0 && rx < data->map_l * TX_L && ry > 0 && ry < data->map_h * TX_L)
        {
            mx = (int) floor(rx / TX_L);
            my = (int) floor(ry / TX_L);
            // printf("mxy at x[%d] y[%d]\n", mx, my);
            // printf("rxy at x[%.2f] y[%.2f]\n", rx, ry);
            if ((mx < 0 || mx >= data->map_l || my < 0 || my >= data->map_h) || (data->map[my][mx] && data->map[my][mx] == '1'))
                break;
            // printf("entered\n");
                if (rx + xo < 0 )
                    rx = 0;
                else if (rx + xo > data->map_l * TX_L)
                    rx = data->map_l * TX_L;
                else
                    rx += xo;
                if (ry + yo < 0)
                    ry = 0;
                else if (ry+ yo > data->map_h * TX_L)
                    ry = data->map_h * TX_L;
                else
                    ry += yo;
        }
        printf("walls found at mx[%d]my[%d]\n", mx, my);
        printf("walls found at rx[%.0f]ry[%.0f]\n", rx, ry);
        dda(data, rx, ry, 0xFF0000);
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    }
}

void    cast_rays(t_data *data)
{
    t_ray   one;
    t_ray   two;

    
}

void init_draw(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	draw_map(data->map, data->map_h, data->map_l, data);
	draw_char(data->map, data->map_h, data->map_l, data);
    printf("pl y --> %dpl x -->%d\n", data->pl_tx_y, data->pl_tx_x);
	printf("y --> %dx -->%d\n", data->pl_y, data->pl_x);
    //my_mlx_pixel_put(data, data->ray.x, data->ray.y, 0xFF0000);
    //dda(data, data->ray.x, data->ray.y, 0xFF0000);
    cast_rays(data);
    ray_till_wall_v(data);
    //printf("x is %.0f  y is %.0f\n", data->ray.x, data->ray.y);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}