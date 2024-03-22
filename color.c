/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:45:37 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/22 03:17:43 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
int		world_color(float percent)
{
    if (percent < 0.001)
        return create_trgb(0, 0, 51, 102); // Deep blue for deep ocean
    else if (percent < 0.007)
        return create_trgb(0, 51, 153, 255); // Medium blue for normal height water
    else if (percent < 0.009)
        return create_trgb(0, 102, 204, 255); // Light aqua for coastal regions
    else if (percent < 0.01)
        return create_trgb(0, 0, 204, 102); // Light green for plains
    else if (percent < 0.1)
        return create_trgb(0, 102, 204, 102); // Medium green for lowlands
    else if (percent < 0.4)
        return create_trgb(0, 153, 102, 51); // Brown for hills and plateaus
	else if (percent < 0.8)
		return create_trgb(0, 153, 102, 51); // Dark brown for high mountain ranges
    else
        return create_trgb(0, 255, 255, 255); // White for snow-capped peaks
}

int		make_color(float percent, int flag, int r, int g)
{
	if (flag == 0)
		return (0x7FFFD4);
	if (flag == 1)
		return (create_trgb(0, g, r, 0));
	if (flag == 2)
		return (create_trgb(0, 0, r, g));
	if (flag == 3)
		return (create_trgb(0, g, 0, r));
	if (flag == 4)
		return (create_trgb(0, r, g, g));
	if (flag == 5)
		return (create_trgb(0, g, r, g));
	if (flag == 6)
		return (create_trgb(0, g / 3, r / 0.5, r / 1.25));
	if (flag == 7)
		return (world_color(percent));
	return (0);
}

int	percent_to_color(float percent, int flag)
{
	int	r;
	int	g;

	r = 255;
	g = 255;
	if (percent < 0.5)
		g = (255 * percent / 0.5);
	else
		r = 255 - (255 * (percent - 0.5) / 0.5);
	return (make_color(percent, flag, r, g));
}
