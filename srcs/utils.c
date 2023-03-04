/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misrailo <misrailo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:23:53 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/04 15:34:14 by misrailo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		printf("Error : Direction utilized in incorrect manner\n");
	if (n == 6)
		printf("Error : Impossible to enter area found on the map\n");
	if (n == 7)
		printf("Error : Hole in the map\n");
	if (n == 8)
		printf("Error : Wall error\n");
	return (WRONG);
}

int	ft_mapsize(char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E' || line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue ;
		}
		i++;
		free(line);
	}
	i++;
	close(fd);
	return (i - 2);
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

int	ft_ischar(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	else
		return (0);
}

int	ft_exit(void)
{
	exit(0);
}

void	change_pos(t_data *data, int j, int i)
{
	int	ii;
	int	jj;

	data->map[(int)data->pl_tx_y / TX_L][(int)data->pl_tx_x / TX_L] = '0';
	data->map[j / TX_L][i / TX_L] = data->player;
	data->pl_x = i / TX_L;
	data->pl_y = j / TX_L;
}
