/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_n_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 21:33:34 by inazarin          #+#    #+#             */
/*   Updated: 2018/10/14 21:33:47 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		free_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void		free_int_array(int n_of_lines, int **data)
{
	int		i;

	i = 0;
	while (i < n_of_lines)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void		free_dot_array(t_fdf *fdf, int flag)
{
	int		i;
	int		j;

	i = 0;
	while (i < (fdf->n_of_lines))
	{
		j = 0;
		while (j < fdf->lenght)
		{
			DOT[i][j].x = 0;
			DOT[i][j].y = 0;
			DOT[i][j].z = 0;
			j++;
		}
		free(DOT[i]);
		i++;
	}
	if (DOT)
		free(DOT);
	if (flag == 1 && fdf->buffer)
		free(fdf->buffer);
}

void		write_data_array(t_fdf *fdf)
{
	char	**tab;
	char	**tab2;
	int		i;
	int		j;

	DOT = (t_dot **)malloc(sizeof(t_dot) * (fdf->n_of_lines));
	tab = ft_strsplit(fdf->buffer, '\n');
	i = -1;
	while (tab[++i])
	{
		DOT[i] = (t_dot *)malloc(sizeof(t_dot) * (fdf->lenght));
		tab2 = ft_strsplit(tab[i], ' ');
		j = -1;
		while (tab2[++j])
		{
			DOT[i][j].x = j * fdf->step + fdf->shift;
			DOT[i][j].y = i * fdf->step + fdf->shift;
			DOT[i][j].z = ft_atoi(tab2[j]) * fdf->step + fdf->shift;
		}
		free_tab(tab2);
	}
	free_tab(tab);
}
