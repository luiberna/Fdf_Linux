/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:26:17 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/25 15:27:37 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_x(t_fdf *fdf, float *x, float *y, float *z)
{
	float	temp_y;
	float	temp_z;

	(void)x;
	temp_y = *y;
	temp_z = *z;
	*y = temp_y * cos(fdf->iso.alpha) + (temp_z) * sin(fdf->iso.alpha);
	*z = -temp_y * sin(fdf->iso.alpha) + (temp_z) * cos(fdf->iso.alpha);
}

void	rotation_y(t_fdf *fdf, float *x, float *y, float *z)
{
	float	temp_x;
	float	temp_z;

	(void)y;
	temp_x = *x;
	temp_z = *z;
	*x = temp_x * cos(fdf->iso.beta) + (temp_z) * sin(fdf->iso.beta);
	*z = -temp_x * sin(fdf->iso.beta) + (temp_z) * cos(fdf->iso.beta);
}

void	rotation_z(t_fdf *fdf, float *x, float *y, float *z)
{
	float	temp_x;
	float	temp_y;

	(void)z;
	temp_x = *x;
	temp_y = *y;
	*x = temp_x * cos(fdf->iso.delta) - temp_y * sin(fdf->iso.delta);
	*y = temp_x * sin(fdf->iso.delta) + temp_y * cos(fdf->iso.delta);
}
