/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:04:34 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/22 16:40:05 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
int     movement_keys(int keysym , t_fdf *fdf)
{
    if (keysym == 'a') //left(A)
		fdf->camera.offset_x -= 15;
	if (keysym == 'd') //right(D)
		fdf->camera.offset_x += 15;
	if (keysym == 'w') //up(W)
		fdf->camera.offset_y -= 15;
	if (keysym == 's') //down(S)
		fdf->camera.offset_y += 15;
    return(0);
}
int     rotation_keys(int keysym, t_fdf *fdf)
{
    if (keysym == 'e') //rotate(E)
		fdf->iso.delta += 0.03;
	if (keysym == 'q') //rotate(Q)
		fdf->iso.delta -= 0.03;
	if (keysym == 'g') //rotate(G)
		fdf->iso.angle_y += 0.03;
	if (keysym == 'h') //rotate(H)
		fdf->iso.angle_y -= 0.03;
    return(0);
}
int     camera_keys(int keysym, t_fdf *fdf)
{
    if (keysym == 61) //z(+)
		fdf->iso.format_z -= 1;
	if (keysym == 45) //z(-)
		fdf->iso.format_z += 1;
	if (keysym == 'l') //projections(L)
		fdf->camera.projection += 1;
	if (fdf->camera.projection > 3)
		fdf->camera.projection = 1;
    if (keysym == ARROW_UP) //arrowup
		fdf->camera.size_grid += 1;
	if (keysym == ARROW_DOWN) //arrowdown
	{
		fdf->camera.size_grid -= 1;
		if (fdf->camera.size_grid < 1)
			fdf->camera.size_grid = 1;
	}
	if (keysym == 'c') //Color (C)
	{
		fdf->flag++;
		if (fdf->flag == 8)
			fdf->flag = 0;
	}
    return(0);
}

int     handle_keys(int keysym, t_fdf *fdf)
{
	if (keysym == ESCAPE)
		free_fdf(fdf);
    if (keysym == 'a' || keysym == 's' || keysym == 'd' || keysym == 'w')
        movement_keys(keysym, fdf);
    if (keysym == 'e' || keysym == 'q' || keysym == 'g' || keysym == 'h')
        rotation_keys(keysym, fdf);
    if (keysym == 45 || keysym == 61 || keysym == 'l' || keysym == ARROW_UP \
		|| keysym == ARROW_DOWN || keysym == 'c')
	{
        camera_keys(keysym, fdf);
	}
    // printf("key: %d\n", keysym);
	clean_image(fdf);
	return (0);
}
