/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_alg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:04:00 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/25 16:22:15 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf **fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= MY_RES_X && y >= 0 && y <= MY_RES_Y)
	{
		dst = (*fdf)->data_addr + (y * (*fdf)->line_lenght + x * ((*fdf)->bpp
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	treat_edge(t_fdf *fdf, t_map_3d a, t_map_3d b, float x)
{
	int	y;

	y = a.y;
	fdf->rgb_percent += fdf->range_z / (fdf->camera.size_grid);
	while (fabs(b.y - y) > 0.5)
	{
		my_mlx_pixel_put(&fdf, x, y, percent_to_color(fdf->rgb_percent,
				fdf->flag));
		y += ((b.y - a.y) / (fabs(b.y - a.y)));
	}
	return ;
}

void	init_line(t_fdf *fdf, t_map_3d a, t_map_3d b, float x)
{
	fdf->rgb_percent = a.z / fdf->new_max;
	if (b.z - a.z > 0)
		fdf->range_z = (b.z / fdf->new_max - fdf->rgb_percent);
	else
		fdf->range_z = -(a.z / fdf->new_max - b.z / fdf->new_max);
	if (fabs(b.x - a.x) <= 0.5 && fabs(b.y - a.y) > 0.5)
		treat_edge(fdf, a, b, x);
	fdf->steep = (b.y - a.y) / (b.x - a.x);
	fdf->direction = (b.x - a.x) / (fabs(b.x - a.x));
}

void	draw_line(t_fdf *fdf, t_map_3d a, t_map_3d b)
{
	float	x;
	float	y;

	projections(&a.x, &a.y, &a.z, fdf);
	projections(&b.x, &b.y, &b.z, fdf);
	x = a.x;
	init_line(fdf, a, b, x);
	while (fabs(b.x - x) > 0.5)
	{
		y = (fdf->steep) * (x - a.x) + a.y;
		fdf->rgb_percent += fdf->range_z / (fdf->camera.size_grid);
		my_mlx_pixel_put(&fdf, round(x), round(y),
			percent_to_color(fdf->rgb_percent, fdf->flag));
		if ((fabs(y - (fdf->steep * ((x + fdf->direction) - a.x) + a.y))) > 1)
		{
			while ((int)(y - (fdf->steep * ((x + fdf->direction) - a.x) + a.y)))
			{
				y = y + ((b.y - a.y) / (fabs(b.y - a.y)));
				my_mlx_pixel_put(&fdf, x, y, percent_to_color(fdf->rgb_percent,
						fdf->flag));
			}
		}
		x = x + fdf->direction;
	}
}

void	draw_baby(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->map->height)
	{
		i = 0;
		while (i < fdf->map->width - 1)
		{
			draw_line(fdf, fdf->map->map_3d[j][i], fdf->map->map_3d[j][i + 1]);
			i++;
		}
		j++;
	}
	j = 0;
	while (j < fdf->map->height - 1)
	{
		i = -1;
		while (i++ < fdf->map->width - 1)
			draw_line(fdf, fdf->map->map_3d[j][i], fdf->map->map_3d[j + 1][i]);
		j++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}
