/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:04:34 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/25 15:22:59 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	movement_keys(int keysym, t_fdf *fdf)
{
	if (keysym == 'a')
		fdf->camera.offset_x -= 15;
	if (keysym == 'd')
		fdf->camera.offset_x += 15;
	if (keysym == 'w')
		fdf->camera.offset_y -= 15;
	if (keysym == 's')
		fdf->camera.offset_y += 15;
	return (0);
}

int	rotation_keys(int keysym, t_fdf *fdf)
{
	if (keysym == 'e')
		fdf->iso.delta += 0.03;
	if (keysym == 'q')
		fdf->iso.delta -= 0.03;
	if (keysym == 'g')
		fdf->iso.angle_y += 0.03;
	if (keysym == 'h')
		fdf->iso.angle_y -= 0.03;
	return (0);
}

int	camera_keys(int keysym, t_fdf *fdf)
{
	if (keysym == 61)
		fdf->iso.format_z -= 1;
	if (keysym == 45)
		fdf->iso.format_z += 1;
	if (keysym == 'l')
		fdf->camera.projection += 1;
	if (fdf->camera.projection > 3)
		fdf->camera.projection = 1;
	if (keysym == ARROW_UP)
		fdf->camera.size_grid += 1;
	if (keysym == ARROW_DOWN)
	{
		fdf->camera.size_grid -= 1;
		if (fdf->camera.size_grid < 1)
			fdf->camera.size_grid = 1;
	}
	if (keysym == 'c')
	{
		fdf->flag++;
		if (fdf->flag == 8)
			fdf->flag = 0;
	}
	return (0);
}

int	handle_keys(int keysym, t_fdf *fdf)
{
	if (keysym == ESCAPE)
		free_fdf(fdf);
	if (keysym == 'a' || keysym == 's' || keysym == 'd' || keysym == 'w')
		movement_keys(keysym, fdf);
	if (keysym == 'e' || keysym == 'q' || keysym == 'g' || keysym == 'h')
		rotation_keys(keysym, fdf);
	if (keysym == 45 || keysym == 61 || keysym == 'l' || keysym == ARROW_UP
		|| keysym == ARROW_DOWN || keysym == 'c')
	{
		camera_keys(keysym, fdf);
	}
	clean_image(fdf);
	return (0);
}
