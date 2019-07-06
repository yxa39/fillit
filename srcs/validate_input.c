/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:38:55 by yxie              #+#    #+#             */
/*   Updated: 2019/07/05 10:20:00 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	validate_format(int fd, int col, int row, int count)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		col = 0;
		row++;
		if (row >= 5 && row % 5 == 0 && ft_strcmp(line, "") != 0)
			return (0);
		while (row % 5 != 0 && line[col])
		{
			if (!(line[col] == '.' || line[col] == '#'))
				return (0);
			if (line[col] == '#')
				count++;
			col++;
		}
		if (row % 5 != 0 && col != 4)
			return (0);
		if (row % 5 == 4 && count != 4)
			return (0);
		if (row % 5 == 4)
			count = 0;
		free(line);
	}
	return (1);
}

int	validate_blocks(char *file_name, int m, int n, int touch_side)
{
	t_blocks *blks;

	blks = create_blocks(file_name, num_of_tetris(file_name));
	while (blks->n < blks->num)
	{
		m = 1;
		touch_side = 0;
		while (m < 4)
		{
			n = -1;
			while (n++ < m)
			{
				if ((blks->x[blks->n][m] == (blks->x[blks->n][n] + 1) &&
blks->y[blks->n][m] == blks->y[blks->n][n]) || (blks->x[blks->n][m] ==
blks->x[blks->n][n] && blks->y[blks->n][m] == (blks->y[blks->n][n] + 1)))
					touch_side++;
			}
			m++;
		}
		if (touch_side < 3)
			return (0);
		blks->n++;
	}
	free(blks);
	return (1);
}

int	validate_input(char *file_name)
{
	int			fd;
	char		buff[BUFF_SIZE + 1];
	int			a;
	int			b;
	int			c;

	a = 0;
	b = 0;
	c = 0;
	fd = open(file_name, O_RDONLY);
	if (read(fd, buff, BUFF_SIZE) <= 0)
		return (0);
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (validate_format(fd, a, b, c) == 0)
		return (0);
	if (num_of_tetris(file_name) > 26)
		return (0);
	if (validate_blocks(file_name, a, b, c) == 0)
		return (0);
	return (1);
}
