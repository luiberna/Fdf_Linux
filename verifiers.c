/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:42:42 by luiberna          #+#    #+#             */
/*   Updated: 2024/03/25 16:56:29 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_name_veri(char *map_name)
{
	char	*s;
	int		len;

	s = ".fdf";
	len = ft_strlen(map_name);
	if (ft_strncmp(&map_name[len - 4], s, 4))
		return (write(2, "Error, not .fdf file\n", 22), 1);
	else
		return (0);
}

void	empty_line_veri(t_fdf *fdf, char *line)
{
	if (line == NULL)
	{
		write(2, "Error, empty file\n", 19);
		free_fdf(fdf);
	}
}

int	line_digit_veri(t_fdf *fdf, char *line)
{
	char	**temp;
	int		i;
	int		line_size;
	char	*trim_line;

	line_size = 0;
	if (!line)
		return (0);
	trim_line = ft_strtrim(line, " \n");
	temp = ft_split(trim_line, ' ');
	free(trim_line);
	while (temp[line_size])
	{
		i = 0;
		while (temp[line_size][i] && temp[line_size][i] != '\n')
		{
			if (temp[line_size][i] == '-' && i == 0)
				i++;
			if (!ft_isdigit(temp[line_size][i]) || !temp[line_size][i])
				free_split(temp, 1, fdf, line);
			i++;
		}
		line_size++;
	}
	return (free_split(temp, 0, fdf, line), line_size);
}

int	map_digit_veri(int fd, t_fdf *fdf)
{
	char	*line;
	int		line_size;
	int		line_size_check;

	line = get_next_line(fd);
	empty_line_veri(fdf, line);
	line_size = line_digit_veri(fdf, line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
			line_size_check = line_digit_veri(fdf, line);
		if (line_size_check != line_size)
		{
			free(line);
			write(2, "Error, invalid map size\n", 25);
			free_fdf(fdf);
		}
	}
	free(line);
	return (0);
}

void	map_veri(t_fdf *fdf)
{
	int	fd;

	if (map_name_veri(fdf->map->map_name))
		free_fdf(fdf);
	else
	{
		fd = open(fdf->map->map_name, O_RDONLY);
		if (fd == -1)
		{
			write(2, "Error, that file is not in the repository\n", 43);
			free_fdf(fdf);
		}
		else if (map_digit_veri(fd, fdf))
		{
			close(fd);
			free_fdf(fdf);
		}
	}
}
