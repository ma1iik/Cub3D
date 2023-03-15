/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:27:23 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/15 09:57:24 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_fill_map(t_data *data, char *file, int i, int j)
{
	char	*l;
	int		gnl;
	int		fd;

	gnl = 1;
	fd = open(file, O_RDONLY);
	while (gnl >= 0)
	{
		gnl = get_next_line(fd, &l);
		if (gnl == 0)
		{
			if (j >= data->m_fl && j <= data->m_ll)
				data->map[i++] = ft_strdup(l);
			break ;
		}
		if (j >= data->m_fl && j <= data->m_ll)
			data->map[i++] = ft_strdup(l);
		free (l);
		j++;
	}
	data->map[i] = NULL;
	close (fd);
	if (ft_fill_map2(data) == WRONG || ft_fill_map3(data) == WRONG)
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
				tmp[j] = '*';
			else
				tmp[j] = data->map[i][j];
			j++;
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
	mlx_hook(data->win, ON_DESTROY, 0, ft_exit, NULL);
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, ft_action, data);
	mlx_key_hook(data->win, ft_release, data);
	mlx_loop(data->mlx);
}
