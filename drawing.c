/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 20:31:39 by inazarin          #+#    #+#             */
/*   Updated: 2018/10/14 20:31:42 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			zoom_helper(t_fdf *fdf, int key)
{
	double		result;

	result = 0.0;
	fdf->x_centre = (DOT[0][0].x + DOT[0][(fdf->lenght - 1)].x) / 2;
	fdf->y_centre = (DOT[(fdf->n_of_lines - 1)][0].y + DOT[0][0].y) / 2;
	fdf->shift = 0;
	if (key == 78)
		result = 0.9;
	else if (key == 69)
		result = 1.1;
	return (result);
}

void			try_zoom(t_fdf *fdf, int key)
{
	int			i;
	int			j;
	double		changer;
	double		tmp_x_center;
	double		tmp_y_center;

	i = -1;
	tmp_x_center = fdf->x_centre;
	tmp_y_center = fdf->x_centre;
	changer = zoom_helper(fdf, key);
	shift_coords(fdf, 0);
	while (++i < fdf->n_of_lines)
	{
		j = -1;
		while (++j < fdf->lenght)
		{
			DOT[i][j].x *= changer;
			DOT[i][j].y *= changer;
			DOT[i][j].z *= changer;
		}
	}
	shift_coords(fdf, 1);
	fdf->x_centre = tmp_x_center;
	fdf->y_centre = tmp_y_center;
	combine_line_and_data(fdf);
}

static void		line_math_helper(t_fdf *fdf, int x_1, int y_1)
{
	fdf->d_x = abs(x_1 - fdf->start_x0);
	fdf->d_y = abs(y_1 - fdf->start_y0);
	if (fdf->start_x0 < x_1)
		fdf->s_x = 1;
	else
		fdf->s_x = -1;
	if (fdf->start_y0 < y_1)
		fdf->s_y = 1;
	else
		fdf->s_y = -1;
	if (fdf->d_x > fdf->d_y)
		fdf->err1 = fdf->d_x / 2;
	else
		fdf->err1 = -fdf->d_y / 2;
}

static void		line(t_fdf *fdf, int x_1, int y_1)
{
	int			x_0;
	int			y_0;

	x_0 = fdf->start_x0;
	y_0 = fdf->start_y0;
	line_math_helper(fdf, x_1, y_1);
	while (1)
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x_0, y_0, fdf->tmp_color);
		if (x_0 == x_1 && y_0 == y_1)
			break ;
		fdf->err2 = fdf->err1;
		if (fdf->err2 > -fdf->d_x)
		{
			fdf->err1 -= fdf->d_y;
			x_0 += fdf->s_x;
		}
		if (fdf->err2 < fdf->d_y)
		{
			fdf->err1 += fdf->d_x;
			y_0 += fdf->s_y;
		}
	}
}

void			combine_line_and_data(t_fdf *fdf)
{
	int			i;
	int			j;

	i = -1;
	if (fdf->one_dot == 1)
		mlx_pixel_put(PTR, WIN, fdf->one_d_x, fdf->one_d_y, fdf->tmp_color);
	while (++i < fdf->n_of_lines)
	{
		j = -1;
		while (++j < fdf->lenght)
		{
			fdf->start_x0 = DOT[i][j].x;
			fdf->start_y0 = DOT[i][j].y;
			if (j < (fdf->lenght - 1) && i < (fdf->n_of_lines - 1))
			{
				line(fdf, DOT[i + 1][j].x, DOT[i + 1][j].y);
				line(fdf, DOT[i][j + 1].x, DOT[i][j + 1].y);
			}
			else if (i == (fdf->n_of_lines - 1) && j < (fdf->lenght - 1))
				line(fdf, DOT[i][j + 1].x, DOT[i][j + 1].y);
			else if (j == (fdf->lenght - 1) && i < (fdf->n_of_lines - 1))
				line(fdf, DOT[i + 1][j].x, DOT[i + 1][j].y);
		}
	}
	draw_instruction(fdf);
}
