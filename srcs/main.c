/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 09:56:41 by yxie              #+#    #+#             */
/*   Updated: 2019/07/03 10:53:11 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

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
	if (validate_input(argv[1]) == 0)
	{
		ft_putstr("error\n");
		return (-1);
	}
	else
	{
		num_tetris = num_of_tetris(argv[1]);
		blocks = create_blocks(argv[1], num_tetris);
		board = create_first_board(square_size(num_tetris));
		solve(board, blocks);
	}
	system("leaks fillit");
	return (0);
}
