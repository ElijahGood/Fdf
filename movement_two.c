/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 20:24:25 by inazarin          #+#    #+#             */
/*   Updated: 2018/10/14 20:24:26 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			go_up(t_fdf *fdf, int key)
{
	int			i;
	int			j;
	int			changer;

	changer = -10;
	key == 125 ? changer *= -1 : (0);
	i = 0;
	while (i < fdf->n_of_lines)
	{
		j = 0;
		while (j < fdf->lenght)
		{
			DOT[i][j].y += changer;
			j++;
		}
		i++;
	}
	if (fdf->one_dot == 1)
	{
		if (key == 125)
			fdf->one_d_y += 1;
		else
			fdf->one_d_y -= 1;
		mlx_pixel_put(PTR, WIN, fdf->one_d_x, fdf->one_d_y, fdf->tmp_color);
	}
}

void			rotate_map_y_left(t_fdf *fdf)
{
	int			i;
	int			j;
	double		rad;
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
			temp_x = DOT[i][j].x;
			DOT[i][j].x = (DOT[i][j].x * cos(rad)) - (DOT[i][j].z * sin(rad));
			DOT[i][j].z = (DOT[i][j].z * cos(rad)) + (temp_x * sin(rad));
			j++;
		}
		i++;
	}
	shift_coords(fdf, 1);
}

void			rotate_map_y_right(t_fdf *fdf)
{
	int			i;
	int			j;
	double		rad;
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
			temp_x = DOT[i][j].x;
			DOT[i][j].x = (DOT[i][j].x * cos(rad)) + (DOT[i][j].z * sin(rad));
			DOT[i][j].z = (DOT[i][j].z * cos(rad)) - (temp_x * sin(rad));
			j++;
		}
		i++;
	}
	shift_coords(fdf, 1);
}

void			rotate_map_x_up(t_fdf *fdf)
{
	int			i;
	int			j;
	double		rad;
	double		temp_y;

	i = 0;
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	shift_coords(fdf, 0);
	rad = 5 * 3.14 / 180;
	while (i < (fdf->n_of_lines))
	{
		j = 0;
		while (j < (fdf->lenght))
		{
			temp_y = DOT[i][j].y;
			DOT[i][j].y = (DOT[i][j].y * cos(rad)) - (DOT[i][j].z * sin(rad));
			DOT[i][j].z = (DOT[i][j].z * cos(rad)) + (temp_y * sin(rad));
			j++;
		}
		i++;
	}
	shift_coords(fdf, 1);
}

void			rotate_map_x_down(t_fdf *fdf)
{
	int			i;
	int			j;
	double		rad;
	double		temp_y;

	i = 0;
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	shift_coords(fdf, 0);
	rad = 5 * 3.14 / 180;
	while (i < (fdf->n_of_lines))
	{
		j = 0;
		while (j < (fdf->lenght))
		{
			temp_y = DOT[i][j].y;
			DOT[i][j].y = (DOT[i][j].y * cos(rad)) + (DOT[i][j].z * sin(rad));
			DOT[i][j].z = (-temp_y * sin(rad)) + (DOT[i][j].z * cos(rad));
			j++;
		}
		i++;
	}
	shift_coords(fdf, 1);
}
