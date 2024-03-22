/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:00:23 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/21 17:07:54 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_fdf(t_fdf *fdf)
{
	int		fd;
	
	map_veri(fdf);
	fd = open(fdf->map->map_name, O_RDONLY);
	map_load(fdf, fd, 0);
	// print_map_info(fdf);
	fill_map_3d(fdf);
	// print_map_3d(fdf);
	mlx_hook(fdf->win_ptr, 2, 1L << 0, handle_keys, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, free_fdf, fdf);
	// mlx_mouse_hook(fdf->win_ptr, handle_mouse, fdf);
	draw_baby(fdf);
}

int		main(int argc, char **argv)
{
	t_fdf *fdf;

	if (argc != 2)
		return (write(2, "Error, use: ./fdf <file>\n", 26), 0);
	fdf = fdf_init(argv[1]);
	fdf->map = map_init(argv[1]);
	make_fdf(fdf);
	mlx_loop(fdf->mlx_ptr);
}
