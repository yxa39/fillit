/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 09:56:41 by yxie              #+#    #+#             */
/*   Updated: 2019/07/01 15:18:13 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"


int	is_safe(t_board current, t_blocks blocks)
{
	int	count;

	count = 1;
	while (count < 4)
	{
		if (current.j + (blocks.x[blocks.n][count] - blocks.x[blocks.n][0]) < 0 ||
			   	current.j + (blocks.x[blocks.n][count] - blocks.x[blocks.n][0]) >= current.size)
			return (0);
		if (current.i + (blocks.y[blocks.n][count] - blocks.y[blocks.n][0]) >= current.size)
			return (0);
		if (*(current.array + (current.i + (blocks.y[blocks.n][count] -
blocks.y[blocks.n][0])) * (current.size + 1) + (current.j +
(blocks.x[blocks.n][count] - blocks.x[blocks.n][0]))) != '.')
			return (0);
		count++;
	}
	return (1);
}

void	place_block(t_board *current, t_blocks blocks)
{
	int	count;

	count = 1;
	*(current->array + current->i * (current->size + 1) + current->j) = blocks.n + 'A';
	while (count < 4)
	{
		*(current->array + (current->i + (blocks.y[blocks.n][count] - blocks.y[blocks.n][0])) * (current->size + 1) + (current->j +(blocks.x[blocks.n][count] - blocks.x[blocks.n][0]))) = blocks.n + 'A';
		count++;
	}
}

int	add_block(t_board *current, t_blocks *blocks)
{
	while (current->i < current->size)
	{
		while (current->j < (current->size))
		{
			if (*(current->array + current->i * (current->size + 1) + current->j) == '.')
			{
				if (is_safe(*current, *blocks))
				{
					place_block(current, *blocks);
					current->j++;
					return (1);
				}
			}
			current->j++;
		}
		current->i++;
		current->j = 0;
	}
	return (0);
}



void delete_last_block(t_board *board)
{
	t_board	*tmp;
	t_board *tmp_1;

	tmp = board;
	while (tmp->next != NULL)
	{
		tmp_1 = tmp;
		tmp = tmp->next;
	}
	free(tmp);
	tmp_1->next = NULL;
}

int	main(int argc, char **argv)
{
	int			num_tetris;
	t_blocks	*blocks;
	t_board		*board;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit file");
		return (1);
	}
/*	validate(file_name);*/
	num_tetris = num_of_tetris(argv[1]);
	blocks = create_blocks(argv[1], num_tetris);
	board = create_first_board(square_size(num_tetris));
	solve(board, blocks);
	return (0);
}
