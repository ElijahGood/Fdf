/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:49:09 by inazarin          #+#    #+#             */
/*   Updated: 2018/10/16 19:49:10 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		reset_figure(t_fdf *fdf)
{
	free_dot_array(fdf, 0);
	fdf->tmp_color = 16777215;
	fdf->shift = fdf->init_shift;
	write_data_array(fdf);
	mlx_clear_window(PTR, WIN);
	rotate_map_x_up(fdf);
	rotate_map_y_right(fdf);
	rotate_map_x_up(fdf);
	rotate_map_y_right(fdf);
	rotate_map_z_back(fdf);
	rotate_map_x_up(fdf);
	combine_line_and_data(fdf);
}

void		error_exit(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	exit(0);
}

int			exit_now(t_fdf *fdf)
{
	if (fdf)
		free_dot_array(fdf, 1);
	exit(1);
	return (0);
}

void		draw_instruction(t_fdf *fdf)
{
	mlx_string_put(PTR, WIN, WIN_W / 100 * 40, WIN_H / 100 * 80,
		0xFFFFFFF, "Instructions");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 12, WIN_H / 100 * 85,
		0xFFFFFFF, "Movement");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 2, WIN_H / 100 * 90,
		0xFFFFFFF, "Right, Left, Up, Down");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 38, WIN_H / 100 * 85,
		0xFFFFFFF, "Zoom");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 37, WIN_H / 100 * 90,
		0xFFFFFFF, "|+ -|");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 52, WIN_H / 100 * 85,
		0xFFFFFFF, "Rotation");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 50, WIN_H / 100 * 90,
		0xFFFFFFF, "1 2 4 6 8 9");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 70, WIN_H / 100 * 85,
		0xFFFFFFF, "Color");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 70, WIN_H / 100 * 90,
		0xFFFFFFF, "|1-7|");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 81, WIN_H / 100 * 85,
		0xFFFFFFF, "Reset");
	mlx_string_put(PTR, WIN, WIN_W / 100 * 84, WIN_H / 100 * 90,
		0xFFFFFFF, "R");
}
