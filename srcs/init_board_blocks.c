/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_board_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:34:30 by yxie              #+#    #+#             */
/*   Updated: 2019/07/02 17:18:41 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		save_coordinates(t_blocks *blocks, int fd, int x, int y)
{
	int		count;
	char	*line;

	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		if (ft_strcmp(line, "") == 0)
		{
			blocks->n++;
			y = 0;
			count = 0;
		}
		while (*line)
		{
			if (*line == '#')
			{
				blocks->x[blocks->n][count] = x;
				blocks->y[blocks->n][count++] = y;
			}
			line++;
			x++;
		}
		y++;
	}
}

t_blocks	*create_blocks(char *file_name, int num_tetris)
{
	int			fd;
	t_blocks	*blocks;
	char		*line;
	int			x;
	int			y;

	blocks = (t_blocks *)malloc(sizeof(t_blocks));
	fd = open(file_name, O_RDONLY);
	blocks->num = num_tetris;
	blocks->n = 0;
	y = 0;
	save_coordinates(blocks, fd, x, y);
	close(fd);
	blocks->n = 0;
	return (blocks);
}

t_board		*create_first_board(int size)
{
	t_board	*board;
	char	*tmp;

	board = (t_board *)malloc(sizeof(t_board));
	board->i = 0;
	board->size = size;
	board->str = (char *)malloc((board->size + 1) *
			board->size * sizeof(char));
	tmp = board->str;
	while (board->i < board->size)
	{
		board->j = 0;
		while (board->j < board->size)
		{
			*tmp++ = '.';
			board->j++;
		}
		*tmp++ = '\0';
		board->i++;
	}
	board->i = 0;
	board->j = 0;
	board->next = NULL;
	return (board);
}

int			num_of_tetris(char *file_name)
{
	int		num_tetris;
	char	*line;
	int		fd;

	num_tetris = 1;
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == '\0')
			num_tetris++;
	}
	close(fd);
	return (num_tetris);
}

int			square_size(int num_tetris)
{
	int	size;

	size = 0;
	while (size < (num_tetris * 4))
	{
		if (size * size >= (num_tetris * 4))
			return (size);
		else
			size++;
	}
	return (0);
}
