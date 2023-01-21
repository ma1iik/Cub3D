/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ma1iik <ma1iik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 01:27:23 by ma1iik            #+#    #+#             */
/*   Updated: 2023/01/21 16:33:43 by ma1iik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

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

void	ft_error(int n)
{
	if (n == 0)
		printf("Wrong\n");
	else
		printf("Wrong\n");
}

int	ft_fill_map(t_data *data, int fd)
{
    char	*line;
    int		gnl;

	(void)data;
	(void)fd;
	// while (gnl > 0)
	// {
	// 	gnl = get_next_line(fd, &line);
	// 	if (line[0] == )
	// }
	return (0);
}

int ft_check_ext(t_data *data, char *file)
{
	int	len;

	len = ft_strlen(file);
	(void)data;
	(void)len;
	printf("ext len --> %d\n", len);
	return (0);
}

int ft_parsing(int ac, t_data *data, char *file)
{
    int     fd;

    if (ac != 2)
    {
        ft_error(0);
        return (WRONG);
    }
    fd = open(file, O_RDONLY);
	ft_check_ext(data, file);
    //ft_fill_map(data, fd);
	close(fd);
    return (0);
}

int main(int ac, char **av)
{
    t_data *data;

	data = ft_calloc(1, sizeof(t_data));
    if (ft_parsing(ac, data, av[1]) == WRONG)
        return (0);
    
}