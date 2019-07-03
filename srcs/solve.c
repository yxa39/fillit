/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:09:28 by yxie              #+#    #+#             */
/*   Updated: 2019/07/03 12:14:11 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*copy_board(char *str, int size)
{
	int		count;
	char	*new;
	char	*tmp;
	int		len;

	count = 0;
	len = size * (size + 1);
	new = (char *)malloc(sizeof(char) * len);
	tmp = new;
	while (count < len)
	{
		*tmp++ = *str++;
		count++;
	}
	return (new);
}

void	create_board(t_board *board)
{
	t_board *new;
	t_board	*tmp;

	tmp = board;
	new = (t_board *)malloc(sizeof(t_board));
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->size = tmp->size;
	new->i = 0;
	new->j = 0;
	new->str = copy_board(tmp->str, tmp->size);
	new->next = NULL;
}

int		new_linked_board(t_board *tmp, t_blocks *blocks, int j, int i)
{
	t_board *current;

	create_board(tmp);
	current = tmp;
	while (current->next != NULL)
		current = current->next;
	current->j = j;
	current->i = i;
	return (add_block(current, blocks));
}

int		fillit(t_board *board, t_blocks *blocks, int j, int i)
{
	t_board *tmp;

	while ((*blocks).n < (*blocks).num)
	{
		tmp = board;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (new_linked_board(tmp, blocks, j, i) == 1)
		{
			blocks->n++;
			tmp = tmp->next;
			i = 0;
			j = 0;
		}
		else
		{
			delete_last_block(board);
			while (tmp->next != NULL)
				tmp = tmp->next;
			j = tmp->j;
			i = tmp->i;
			delete_last_block(board);
			blocks->n--;
			if (blocks->n < 0)
				return (0);
		}
	}
	return (1);
}

void	solve(t_board *board, t_blocks *blocks)
{
	int		size;
	t_board	*new;
	t_board *tmp;

	if (fillit(board, blocks, 0, 0) == 1)
		print_result(board);
	else
	{
		size = (board->size + 1);
		blocks->n = 0;
		new = create_first_board(size);
		return (solve(new, blocks));
	}
}
