/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:38:55 by yxie              #+#    #+#             */
/*   Updated: 2019/07/02 17:16:11 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int	validate_format(int fd)
{
	char	*line;
	int		col;
	int		row;
	int		count;

	row = 0;
	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		col = 0;
		row++;
		if (row >= 5 && row % 5 == 0 && ft_strcmp(line, "") != 0)
			return (0);
		if (row % 5 != 0)
		{
			while (line[col])
			{
				if (!(line[col] == '.' || line[col] == '#'))
					return (0);
				if (line[col++] == '#')
					count++;
			}
			if (col != 4)
				return (0);
		}
		if (row % 5 == 4)
		{
			if (count != 4)
				return (0);
			count = 0;
		}
	}
	return (1);
}

int validate_blocks(char *file_name)
{
	t_blocks	blocks;
	int			count;
	int			n;
	int			touch_side;

	blocks = *create_blocks(file_name, num_of_tetris(file_name));
	while (blocks.n < blocks.num)
	{
		count = 1;
		touch_side = 0;
		while (count < 4)
		{
			n = 0;
			while (n < count)
			{
				if ((blocks.x[blocks.n][count] == (blocks.x[blocks.n][n] + 1) && blocks.y[blocks.n][count] == blocks.y[blocks.n][n]) || (blocks.x[blocks.n][count] == blocks.x[blocks.n][n]  && blocks.y[blocks.n][count] == (blocks.y[blocks.n][n] + 1)))
					touch_side++;
				n++;
			}
			count++;
		}
		if (touch_side < 3)
			return (0);
		blocks.n++;
	}
	return (1);
}

int	validate_input(char *file_name)
{
	int		fd;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	if (read(fd, buff, BUFF_SIZE) <= 0)
		return (0);
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (validate_format(fd) == 0)
		return (0);
	if (validate_blocks(file_name) == 0)
		return (0);
	return (1);
}
