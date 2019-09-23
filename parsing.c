/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazarin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:38:17 by inazarin          #+#    #+#             */
/*   Updated: 2018/09/25 14:38:19 by inazarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char		*ft_strjohn(char const *s1, char const *s2)
{
	char		*new;
	size_t		i;

	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!new)
		return (0);
	while (*s1)
		new[i++] = *s1++;
	new[i++] = '\n';
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	return (new);
}

static int		is_valid(const char *line)
{
	int			i;

	i = 0;
	while (line[++i])
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != ' ' && line[i] != '-')
			return (0);
		else if (line[i] == '-' && (line[i + 1] == '-' || line[i + 1] == ' '
			|| line[i + 1] == '\n' || line[i + 1] == '\0'))
			return (0);
		else if (ft_isdigit(line[i]) == 1 && line[i + 1] == '-')
			return (0);
		i++;
	}
	return (1);
}

static int		check_line_lenght(const char *line)
{
	int			i;
	int			counter;

	i = 0;
	counter = 0;
	if (ft_isdigit(line[0]) || (line[0] == '-' && ft_isdigit(line[1])))
		counter++;
	else
		error_exit(ERR0);
	while (line[i])
	{
		if ((line[i] == ' ' && line[i + 1] != ' ') && (line[i + 1] == '-' ||
			ft_isdigit(line[i + 1])))
			counter++;
		i++;
	}
	return (counter);
}

static void		write_to_buff(t_fdf *fdf, char *line)
{
	char		*temp;

	if (fdf->lenght == 0)
		fdf->lenght = check_line_lenght(line);
	else if (check_line_lenght(line) != fdf->lenght)
		error_exit(ERR0);
	if (fdf->buffer != NULL)
	{
		temp = ft_strdup(fdf->buffer);
		free(fdf->buffer);
		fdf->buffer = ft_strjohn(temp, line);
		free(temp);
	}
	else
		fdf->buffer = ft_strdup(line);
}

void			fdf_parser(t_fdf *fdf, char **av)
{
	char		*line;
	int			fd;
	int			size;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(0);
	while (get_next_line(fd, &line) > 0)
	{
		is_valid(line) ? write_to_buff(fdf, line) : error_exit(ERR0);
		free(line);
		fdf->n_of_lines += 1;
	}
	if (get_next_line(fd, &line) == -1 || get_next_line(fd, &line) == 0)
		exit(0);
	fdf->one_dot = (NOL == 1 && LEN == 1) ? 1 : 0;
	size = WIN_W > WIN_H ? WIN_W : WIN_H;
	fdf->shift = ((size / 100) * 20) / 2;
	fdf->init_shift = ((size / 100) * 20) / 2;
	fdf->one_d_x = WIN_H / 2;
	fdf->one_d_y = WIN_W / 2;
	fdf->step = (double)((size / 100) * 80) / fdf->lenght;
	write_data_array(fdf);
	fdf->x_centre = (DOT[0][0].x + DOT[0][(fdf->lenght - 1)].x) / 2;
	fdf->y_centre = (DOT[(fdf->n_of_lines - 1)][0].y + DOT[0][0].y) / 2;
}
