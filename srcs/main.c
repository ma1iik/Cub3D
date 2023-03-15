/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:27:23 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 20:20:24 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_direction(t_data *data, char player)
{
	if (player == 'N')
	{
		data->pa = M_PI / 2;
	}
	else if (player == 'E')
	{
		data->pa = 0.0000;
	}
	else if (player == 'S')
	{
		data->pa = 3 * M_PI / 2;
	}
	else if (player == 'W')
	{
		data->pa = M_PI;
	}
	return ;
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (ft_parsing(ac, data, av[1]) == WRONG)
		return (WRONG);
	init_draw(data);
	mlx_hook(data->win, ON_DESTROY, 0, ft_exit, data);
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, ft_action, data);
	mlx_key_hook(data->win, ft_release, data);
	mlx_loop(data->mlx);
}
