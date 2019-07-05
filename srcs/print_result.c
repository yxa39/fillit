/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:02:52 by yxie              #+#    #+#             */
/*   Updated: 2019/07/03 12:12:27 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_board(t_board board)
{
	board.i = 0;
	board.j = 0;
	while (board.i < (board.size))
	{
		ft_putstr(board.str + board.i * (board.size + 1));
		ft_putchar('\n');
		board.i++;
	}
}

void	print_result(t_board *board)
{
	t_board *tmp;

	tmp = board;
	while (tmp->next != NULL)
		tmp = tmp->next;
	print_board(*tmp);
}

void	delete_board(t_board *board)
{
	t_board	*tmp;

	while (board != NULL)
	{
		tmp = board;
		board = board->next;
		free(tmp->str);
		free(tmp);
	}
}
