/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:15:32 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/22 17:32:10 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    init_vari(t_fdf *fdf)
{
    fdf->iso.angle_x = 0.523599; //30
    fdf->iso.angle_y = 0.523599; //30
    fdf->iso.alpha = 0;
    fdf->iso.beta = 0;
    fdf->iso.phi = 0;
    fdf->iso.delta = 0;
    fdf->iso.gamma = 0.7854;
    fdf->iso.format_z = 1;
    fdf->camera.offset_x = MY_RES_X / 2;
    fdf->camera.offset_y = 100;
    fdf->camera.size_grid = 10;
    fdf->camera.projection = 1;
    fdf->iso.format_z = 15;
    fdf->flag = 0;
    fdf->rgb_percent = 0;
    fdf->range_z = 0;
    fdf->new_max = 0;
}

t_fdf   *fdf_init(char *path)
{
    t_fdf *fdf;
    char *win_name;

    win_name = ft_strjoin("Fdf - ", path);
    fdf = (t_fdf *)malloc(sizeof(t_fdf));
    if (!fdf)
        return (write(2, "Malloc Error FDF\n", 17), NULL);
    fdf->mlx_ptr = mlx_init();
    if (!fdf->mlx_ptr)
        return (write(2, "Error connecting to MLX\n", 25), NULL);
    fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, MY_RES_X, MY_RES_Y, win_name);
    if (!fdf->win_ptr)
        return (write(2, "Error init window\n", 19), NULL);
    fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, MY_RES_X, MY_RES_Y);
    if (!fdf->img_ptr)
        return (write(2, "Error init image\n", 18), NULL);
    fdf->data_addr = mlx_get_data_addr(fdf->img_ptr, &fdf->bpp, &fdf->line_lenght, &fdf->endian);
    fdf->map = NULL;
    init_vari(fdf);
    free(win_name);
    return (fdf);
}

t_map   *map_init(char *filename)
{
    t_map   *map;
    
    map = (t_map *)malloc(sizeof(t_map));
    map->height = 0;
	map->width = 0;
	map->z_max = 0;
	map->z_min = 0;
	map->steep = 0;
	map->direction = 0;
    map->map_info = NULL;
    map->map_3d = NULL;
    if(!map)
        return (write(2, "Error init map\n", 16), NULL);
    map->map_name = filename;
    return (map);
}
