/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:17:57 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/21 14:16:06 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// //(Test function) - Prints map_3d
// void print_map_3d(t_fdf *fdf)
// {
//     int i;
//     int j;
	
// 	i = 0;
//     while (i < fdf->map->height)
//     {
//         j = 0;
//         while (j < fdf->map->width)
//         {
//             printf("x: %f, y: %f, z: %f\n", fdf->map->map_3d[i][j].x, fdf->map->map_3d[i][j].y, fdf->map->map_3d[i][j].z);
//             j++;
//         }
//         i++;
//     }
// }

// (Test function) - Prints the map_info
// void    print_map_info(t_fdf *fdf)
// {
//     int i;
//     int j;

//     i = 0;
//     while (i < fdf->map->height)
//     {
//         j = 0;
//         while (j < fdf->map->width)
//         {
//             ft_printf("%d ", fdf->map->map_info[i][j]);
//             j++;
//         }
//         ft_printf("\n");
//         i++;
//     }
// }

void    regulate_z(t_fdf *fdf)
{
    if (fdf->map->z_max - fdf->map->z_min > 90)
        fdf->iso.format_z = 9;
    if (fdf->map->z_max - fdf->map->z_min > 900)
        fdf->iso.format_z = 90;
}

void    get_max_min_z(t_fdf *fdf, int nb)
{
    if (!fdf->map->z_max || nb > fdf->map->z_max)
        fdf->map->z_max = nb;
    if (!fdf->map->z_min || nb < fdf->map->z_min)
        fdf->map->z_min = nb;
}

int     *map_split(t_fdf *fdf, char *line)
{
    char    **split;
    int     *line_values;
    int     i;
    int     size;
    
    size = 0;
    i = 0;
    split = ft_split(line, ' ');
    while (split[size])
        size++;
    fdf->map->width = size;
    line_values = malloc(sizeof(int) * size);
    while (i < size)
    {
        line_values[i] = ft_atoi(split[i]);
        get_max_min_z(fdf, line_values[i]);
        free(split[i]);
        i++;
    }
    free(split);
    return(line_values);
}

void    map_load(t_fdf *fdf, int fd, int i)
{
    char    *line;
    
    line = get_next_line(fd);
    fdf->map->height++;
    if (line)
        map_load(fdf, fd, i + 1);
    else
        fdf->map->map_info = malloc(sizeof(int *) * fdf->map->height);
    if (line)
        fdf->map->map_info[i] = map_split(fdf, line);
    else
        fdf->map->map_info[i] = (int *)line;
    free(line);
}
void    fill_map_3d(t_fdf *fdf)
{
    int i;
    int j;

    i = 0;
    fdf->map->map_3d = (t_map_3d **)malloc(sizeof(t_map_3d *) * fdf->map->height--);
    while (i < fdf->map->height)
    {
        fdf->map->map_3d[i] = (t_map_3d *)malloc(sizeof(t_map_3d) * fdf->map->width);
        j = 0;
        while (j < fdf->map->width)
        {
            fdf->map->map_3d[i][j].x = j;
            fdf->map->map_3d[i][j].y = i;
            fdf->map->map_3d[i][j].z = fdf->map->map_info[i][j];
            j++;
        }
        i++;
    }
}
