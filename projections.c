/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:57:42 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/25 15:27:26 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(float *x, float *y, float *z, t_fdf *fdf)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;

	temp_x = *x;
	temp_y = *y;
	temp_z = *z;
	*x = ((temp_x - temp_y) * cos(fdf->iso.angle_x)) * fdf->camera.size_grid
		+ fdf->camera.offset_x;
	*y = ((-(temp_z) / fdf->iso.format_z + (temp_x + temp_y)
				* sin(fdf->iso.angle_y))) * fdf->camera.size_grid
		+ fdf->camera.offset_y;
	if (fdf->map->z_min < 0 || (fdf->map->z_min < 0 && fdf->map->z_max < 0))
	{
		*z = temp_z - fdf->map->z_min + 1;
		fdf->new_max = fdf->map->z_max - fdf->map->z_min + 1;
	}
}

void	parallel_projection(float *x, float *y, float *z, t_fdf *fdf)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;

	temp_x = *x;
	temp_y = *y;
	temp_z = *z;
	*x = ((temp_x - (temp_z / fdf->iso.format_z)) * cos(fdf->iso.gamma))
		* fdf->camera.size_grid + fdf->camera.offset_x;
	*y = ((temp_y - (temp_z / fdf->iso.format_z)) * sin(fdf->iso.gamma))
		* fdf->camera.size_grid + fdf->camera.offset_y;
	if (fdf->map->z_min < 0 || (fdf->map->z_min < 0 && fdf->map->z_max < 0))
	{
		*z = temp_z - fdf->map->z_min + 1;
		fdf->new_max = fdf->map->z_max - fdf->map->z_min + 1;
	}
}

void	front_projection(float *x, float *y, float *z, t_fdf *fdf)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;

	temp_x = *x;
	temp_y = *y;
	temp_z = *z;
	*x = temp_x * fdf->camera.size_grid;
	*y = temp_y * fdf->camera.size_grid;
	if (fdf->map->z_min < 0 || (fdf->map->z_min < 0 && fdf->map->z_max < 0))
	{
		*z = temp_z - fdf->map->z_min + 1;
		fdf->new_max = fdf->map->z_max - fdf->map->z_min + 1;
	}
}

void	projections(float *x, float *y, float *z, t_fdf *fdf)
{
	rotation_z(fdf, x, y, z);
	rotation_y(fdf, x, y, z);
	rotation_x(fdf, x, y, z);
	get_max_min_z(fdf, (int)(*z));
	if (fdf->camera.projection == 1)
		isometric_projection(x, y, z, fdf);
	if (fdf->camera.projection == 2)
		parallel_projection(x, y, z, fdf);
	if (fdf->camera.projection == 3)
		front_projection(x, y, z, fdf);
}
