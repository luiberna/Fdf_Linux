/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:47:04 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/22 17:50:07 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <errno.h>

# define ESCAPE 65307
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define SPACE 49
# define MOUSE_LEFTCLICK 1
# define MOUSE_RIGHTCLICK 2
# define MY_RES_X 1440
# define MY_RES_Y 800

typedef struct s_map_3d
{
	float		x;
	float		y;
	float		z;
}					t_map_3d;

typedef struct s_map
{
	char		*map_name;
	int			**map_info;
	int			height;
	int			width;
	int			z_max;
	int 		z_min;
	float		steep;
	int 		direction;
	t_map_3d	**map_3d;
}					t_map;

typedef struct s_camera
{
	int			offset_x;
	int			offset_y;
	int			zoom;
	int			size_grid;
	int			projection;
	float		color_percent;
	float		color_flag;
}					t_camera;

typedef struct s_isometric
{
	float		angle_x;
	float		angle_y;
	float		alpha;
	float		beta;
	float		delta;
	float		gamma;
	float		phi;
	float		prev_y;
	float		prev_x;
	int			format_z;
}					t_isometric;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data_addr;
	int			bpp;
	int			endian;
	int			line_lenght;
	//
	float		rgb_percent;
	float		range_z;
	int			new_max;
	int			flag;
	//
	t_map		*map;
	t_isometric iso;
	t_camera	camera;
}					t_fdf;

//init
t_fdf 	*fdf_init(char *path);
t_map   *map_init(char *filename);
void    init_vari(t_fdf *fdf);

//verifiers
int		map_name_veri(char *map_name);
void    empty_line_veri(t_fdf *fdf, char *line);
int     line_digit_veri(t_fdf *fdf, char *line);
int     map_digit_veri(int fd, t_fdf *fdf);
void	map_veri(t_fdf *fdf);

//map
void    regulate_z(t_fdf *fdf);
void    get_max_min_z(t_fdf *fdf, int nb);
int     *map_split(t_fdf *fdf, char *line);
void    map_load(t_fdf *fdf, int fd, int i);
void    fill_map_3d(t_fdf *fdf);

//screen

//free
void	clean_image(t_fdf *fdf);
void	free_mlx(t_fdf *fdf);
int		free_fdf(t_fdf *fdf);
void    free_split(char **temp, int flag, t_fdf *fdf, char *line);

//fdf
void	make_fdf(t_fdf *fdf);

//draw
void 	my_mlx_pixel_put(t_fdf **data, int x, int y, int color);
void	treat_edge(t_fdf *fdf, t_map_3d a, t_map_3d b, float x);
void	init_line(t_fdf *fdf, t_map_3d a, t_map_3d b, float x);
void	draw_line(t_fdf *fdf, t_map_3d a, t_map_3d b);
void 	draw_baby(t_fdf *fdf);

//testing
// void    print_map_info(t_fdf *fdf);
// void 	print_map_3d(t_fdf *fdf);

//projections
void    isometric_projection(float *x, float *y, float *z, t_fdf *fdf);
void    parallel_projection(float *x, float *y, float *z, t_fdf *fdf);
void    front_projection(float *x, float *y, float *z, t_fdf *fdf);
void    rotation_x(t_fdf *fdf, float *x, float *y, float *z);
void    rotation_y(t_fdf *fdf, float *x, float *y, float *z);
void    rotation_z(t_fdf *fdf, float *x, float *y, float *z);
void	projections(float *x, float *y, float *z, t_fdf *fdf);

//color
int		world_color(float percent);
int		percent_to_color(float percent, int flag);
int		make_color(float percent, int flag, int r, int g);
int		create_trgb(int t, int r, int g, int b);

//keys
int 	handle_keys(int keysym, t_fdf *fdf);
int     movement_keys(int keysym , t_fdf *fdf);
int     rotation_keys(int keysym, t_fdf *fdf);
int     camera_keys(int keysym, t_fdf *fdf);

#endif