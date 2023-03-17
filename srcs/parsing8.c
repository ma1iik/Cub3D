/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:19:02 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/16 23:15:02 by ma1iik           ###   ########.fr       */
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
			free (l);
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