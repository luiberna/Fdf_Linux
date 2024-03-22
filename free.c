/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:02:07 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/22 17:57:55 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_image(t_fdf *fdf)
{
	int x = 0;
	int y;
	
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	while (x < 1440)
	{
		y = 0;
		while (y < 800)
		{
			my_mlx_pixel_put(&fdf, x, y, 0x00000000);
			y++;
		}
		x++;
	}
	draw_baby(fdf);
}

void free_map(t_map *map)
{
    int i;

    i = 0;
    while (i < map->height)
    {
        free(map->map_info[i]);
        i++;
    }
    i = 0;
    while (i < map->height)
    {
        free(map->map_3d[i]);
        i++;
    }
    free(map->map_info);
    free(map->map_3d);
    free(map);
}

void free_mlx(t_fdf *fdf)
{
    if (fdf->win_ptr)
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
    if (fdf->img_ptr)
        mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
    mlx_destroy_display(fdf->mlx_ptr); //on linux;
    free(fdf->mlx_ptr);
    free(fdf);
}

int free_fdf(t_fdf *fdf)
{
    free_map(fdf->map);
    free_mlx(fdf);
    exit (1);
    // return (0);
}
/* Recieves the split's double pointer, a flag and the struct fdf.
If the flag is 1, the line has a digit and the program should stop */
void    free_split(char **temp, int flag, t_fdf *fdf, char *line)
{
    int     i;
    
    i = 0;
    while (temp[i])
    {
        free(temp[i]);
        i++;
    }
    free(temp);
    if (flag == 1)
    {
        free(line);
        write (2, "Error, non digit in map\n", 25);
        free_fdf (fdf);
    }
}
