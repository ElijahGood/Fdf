/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 21:31:36 by inazarin          #+#    #+#             */
/*   Updated: 2018/09/18 21:31:38 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include <math.h>
# include "mlx.h"

# define ERR0 "(Invalid line)\n"
# define WIN_W 700.0
# define WIN_H 700.0
# define DOT fdf->dots
# define WIN fdf->win_ptr
# define PTR fdf->mlx_ptr
# define LEN fdf->lenght
# define NOL fdf->n_of_lines

typedef struct	s_dot
{
	double		x;
	double		y;
	double		z;
	int			color;

}				t_dot;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*buffer;
	int			lenght;
	int			**data;
	int			n_of_lines;
	int			x_rad;
	int			y_rad;
	int			z_rad;
	int			tmp_rad;
	double		x_centre;
	double		y_centre;
	t_dot		**dots;
	double		step;
	int			init_shift;
	int			shift;
	int			color;
	int			tmp_color;
	int			start_x0;
	int			start_y0;
	int			d_x;
	int			d_y;
	int			s_x;
	int			s_y;
	int			err1;
	int			err2;
	int			one_dot;
	double		one_d_x;
	double		one_d_y;
}				t_fdf;

void			free_dot_array(t_fdf *fdf, int flag);
void			rotate_map_x_down(t_fdf *fdf);
void			rotate_map_y_right(t_fdf *fdf);
void			rotate_map_x_up(t_fdf *fdf);
void			rotate_map_y_left(t_fdf *fdf);
void			combine_line_and_data(t_fdf *fdf);
void			write_data_array(t_fdf *fdf);
void			fdf_parser(t_fdf *fdf, char **av);
void			free_tab(char **tab);
void			error_exit(char *str);
int				exit_now(t_fdf *fdf);
void			rotation_all(t_fdf *fdf, int key);
void			zoom_it(t_fdf *fdf, int key);
void			shift_coords(t_fdf *fdf, int flag);
void			draw_instruction(t_fdf *fdf);
void			go_left(t_fdf *fdf, int key);
void			go_up(t_fdf *fdf, int key);
void			try_zoom(t_fdf *fdf, int key);
void			free_int_array(int n_of_lines, int **data);
void			rotate_map_z_back(t_fdf *fdf);
void			try_zoom(t_fdf *fdf, int key);
void			reset_figure(t_fdf *fdf);

#endif
