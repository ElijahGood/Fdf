/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:38:00 by inazarin          #+#    #+#             */
/*   Updated: 2018/09/25 14:38:03 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		initializer(t_fdf *fdf)
{
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->lenght = 0;
	fdf->buffer = NULL;
	fdf->data = NULL;
	fdf->n_of_lines = 0;
	fdf->x_rad = 0;
	fdf->y_rad = 0;
	fdf->z_rad = 0;
	fdf->x_centre = 0;
	fdf->y_centre = 0;
	fdf->tmp_color = 16777215;
	fdf->start_x0 = 0;
	fdf->start_y0 = 0;
	fdf->tmp_rad = 0;
	fdf->d_x = 0;
	fdf->d_y = 0;
	fdf->s_x = 0;
	fdf->s_y = 0;
	fdf->err1 = 0;
	fdf->err2 = 0;
	fdf->init_shift = 0;
	fdf->one_dot = 0;
}

void		change_color(t_fdf *fdf, int key)
{
	if (key == 18)
		fdf->tmp_color = 16711680;
	else if (key == 19)
		fdf->tmp_color = 16744448;
	else if (key == 20)
		fdf->tmp_color = 16776960;
	else if (key == 21)
		fdf->tmp_color = 65280;
	else if (key == 23)
		fdf->tmp_color = 255;
	else if (key == 22)
		fdf->tmp_color = 8323327;
	else if (key == 26)
		fdf->tmp_color = 16711935;
	else if (key == 25)
		fdf->tmp_color = 0;
	else if (key == 29)
		fdf->tmp_color = 16777215;
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	combine_line_and_data(fdf);
}

int			keys_and_masks(int key, t_fdf *fdf)
{
	if (key == 53)
		exit_now(fdf);
	else if (key == 84 || key == 91 || key == 92 || key == 86 || key == 83 ||
		key == 88 || key == 69 || key == 78 || key == 0 || key == 2 ||
		key == 13 || key == 1 || key == 123 || key == 124 || key == 125 ||
		key == 126)
		rotation_all(fdf, key);
	else if (key == 18 || key == 19 || key == 20 || key == 21 || key == 22 ||
		key == 23 || key == 26 || key == 25 || key == 29)
		change_color(fdf, key);
	else if (key == 15)
		reset_figure(fdf);
	return (0);
}

int			main(int ac, char **av)
{
	t_fdf	fdf;

	initializer(&fdf);
	if (ac != 2)
		exit_now(NULL);
	else
		fdf_parser(&fdf, av);
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_W, WIN_H, "FdF");
	mlx_hook(fdf.win_ptr, 2, 5, keys_and_masks, &fdf);
	mlx_hook(fdf.win_ptr, 17, (1L << 17), exit_now, &fdf);
	rotate_map_x_up(&fdf);
	rotate_map_y_right(&fdf);
	rotate_map_x_up(&fdf);
	rotate_map_y_right(&fdf);
	rotate_map_z_back(&fdf);
	rotate_map_x_up(&fdf);
	combine_line_and_data(&fdf);
	mlx_loop(fdf.mlx_ptr);
	free_int_array(fdf.n_of_lines, fdf.data);
}
