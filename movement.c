/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:38:09 by inazarin          #+#    #+#             */
/*   Updated: 2018/09/25 14:38:10 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			go_left(t_fdf *fdf, int key)
{
	int			i;
	int			j;
	int			changer;

	i = 0;
	changer = -10;
	key == 124 ? changer *= -1 : 0;
	while (i < fdf->n_of_lines)
	{
		j = 0;
		while (j < fdf->lenght)
		{
			DOT[i][j].x += changer;
			j++;
		}
		i++;
	}
	if (fdf->one_dot == 1)
	{
		if (key == 124)
			fdf->one_d_x += 1;
		else
			fdf->one_d_x -= 1;
		mlx_pixel_put(PTR, WIN, fdf->one_d_x, fdf->one_d_y, fdf->tmp_color);
	}
}

void			shift_coords(t_fdf *fdf, int flag)
{
	int			i;
	int			j;

	i = 0;
	while (i < fdf->n_of_lines)
	{
		j = 0;
		while (j < fdf->lenght)
		{
			if (flag == 0)
			{
				DOT[i][j].x = DOT[i][j].x - fdf->x_centre;
				DOT[i][j].y = DOT[i][j].y - fdf->y_centre;
			}
			else if (flag == 1)
			{
				DOT[i][j].x = DOT[i][j].x + fdf->x_centre;
				DOT[i][j].y = DOT[i][j].y + fdf->y_centre;
			}
			j++;
		}
		i++;
	}
}

void			rotate_map_z_back(t_fdf *fdf)
{
	int			i;
	int			j;
	double		rad;
	double		temp_y;
	double		temp_x;

	i = 0;
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	shift_coords(fdf, 0);
	rad = 5 * 3.14 / 180;
	while (i < fdf->n_of_lines)
	{
		j = 0;
		while (j < fdf->lenght)
		{
			temp_y = DOT[i][j].y;
			temp_x = DOT[i][j].x;
			DOT[i][j].x = (DOT[i][j].x * cos(rad)) + (DOT[i][j].y * sin(rad));
			DOT[i][j].y = (temp_y * cos(rad)) - (temp_x * sin(rad));
			j++;
		}
		i++;
	}
	shift_coords(fdf, 1);
}

static void		rotate_map_z(t_fdf *fdf)
{
	int			i;
	int			j;
	double		rad;
	double		temp_y;
	double		temp_x;

	i = 0;
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	shift_coords(fdf, 0);
	rad = 5 * 3.14 / 180;
	while (i < fdf->n_of_lines)
	{
		j = 0;
		while (j < fdf->lenght)
		{
			temp_y = DOT[i][j].y;
			temp_x = DOT[i][j].x;
			DOT[i][j].x = (DOT[i][j].x * cos(rad)) - (DOT[i][j].y * sin(rad));
			DOT[i][j].y = (temp_x * sin(rad)) + (temp_y * cos(rad));
			j++;
		}
		i++;
	}
	shift_coords(fdf, 1);
}

void			rotation_all(t_fdf *fdf, int key)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	if ((key == 78 || key == 69) && fdf->one_dot == 0)
	{
		try_zoom(fdf, key);
		return ;
	}
	if (key == 84 && fdf->one_dot == 0)
		rotate_map_x_down(fdf);
	if (key == 91 && fdf->one_dot == 0)
		rotate_map_x_up(fdf);
	if (key == 88 && fdf->one_dot == 0)
		rotate_map_y_right(fdf);
	if (key == 86 && fdf->one_dot == 0)
		rotate_map_y_left(fdf);
	if (key == 92 && fdf->one_dot == 0)
		rotate_map_z(fdf);
	if (key == 83 && fdf->one_dot == 0)
		rotate_map_z_back(fdf);
	if (key == 123 || key == 124)
		go_left(fdf, key);
	if (key == 126 || key == 125)
		go_up(fdf, key);
	combine_line_and_data(fdf);
}
