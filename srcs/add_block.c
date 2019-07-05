/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:10:03 by yxie              #+#    #+#             */
/*   Updated: 2019/07/05 09:26:51 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		is_safe(t_board current, t_blocks blocks)
{
	int	count;

	count = 1;
	while (count < 4)
	{
		if (current.j + (blocks.x[blocks.n][count] - blocks.x[blocks.n][0]) < 0
	|| current.j + (blocks.x[blocks.n][count] - blocks.x[blocks.n][0]) >=
current.size)
			return (0);
		if (current.i + (blocks.y[blocks.n][count] - blocks.y[blocks.n][0]) >=
				current.size)
			return (0);
		if (*(current.str + (current.i + (blocks.y[blocks.n][count] -
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
	*(current->str + current->i * (current->size + 1) + current->j) =
		blocks.n + 'A';
	while (count < 4)
	{
		*(current->str + (current->i + (blocks.y[blocks.n][count] -
blocks.y[blocks.n][0])) * (current->size + 1) + (current->j +
(blocks.x[blocks.n][count] - blocks.x[blocks.n][0]))) = blocks.n + 'A';
		count++;
	}
}

int		add_block(t_board *current, t_blocks *blocks)
{
	while (current->i < current->size)
	{
		while (current->j < (current->size))
		{
			if (*(current->str + current->i * (current->size + 1) +
						current->j) == '.')
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

void	delete_last_block(t_board *board)
{
	t_board	*tmp;
	t_board *tmp_1;

	tmp = board;
	while (tmp->next != NULL)
	{
		tmp_1 = tmp;
		tmp = tmp->next;
	}
	free(tmp->str);
	free(tmp);
	tmp_1->next = NULL;
}
