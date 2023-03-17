/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:23:53 by ma1iik            #+#    #+#             */
/*   Updated: 2023/03/17 20:36:52 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_error(int n)
{
	if (n == 0)
		printf("Error\nWrong number of arguments\n");
	else if (n == 1)
		printf("Error\nWrong extension of map\n");
	else if (n == 2)
		printf("Error\nMap file is a directory\n");
	else if (n == 3)
		printf("Error\nMap file not read properly\n");
	else if (n == 4)
		printf("Error\nWrong character on map found\n");
	else if (n == 5)
		printf("Error\nPlayer direction utilized in incorrect manner\n");
	else if (n == 6)
		printf("Error\nImpossible to enter area found on the map\n");
	else if (n == 7)
		printf("Error\nHole in the map\n");
	else if (n == 8)
		printf("Error\nWall error\n");
	else if (n == 9)
		printf("Error\nParameters invalid\n");
	else if (n == 11 || n == 10)
		printf("Error\nTexture path is invalid\n");
	exit (1);
	return (WRONG);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
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


