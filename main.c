/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 09:56:41 by yxie              #+#    #+#             */
/*   Updated: 2019/07/01 09:36:00 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

int	validate(char* file_name)
{
	return (0);
}

void	print_blocks(t_blocks blocks)
{
	int	count;

	while (blocks.n < blocks.num)
	{
		count = 0;
		while (count < 4)
		{
			printf("%dth:(%d, %d)\n", blocks.n, (blocks.x)[blocks.n][count], (blocks.y)[blocks.n][count]);
			count++;
		}
		blocks.n++;
	}
}

void	print_board(t_board board)
{
	board.i = 0;
	board.j = 0;
	while (board.i < (board.size))
	{
			printf("%s\n", board.array +  board.i * (board.size + 1));
			board.i++;
	}
}

int	square_size(int num_tetris)
{
	int	size;

	size = 0;
	while (size < (num_tetris * 4))
	{
		if (size * size >= (num_tetris * 4))
			if (size < 4)
				return (4);
			else
				return (size);
		else
			size++;
	}
	return (0);
}

t_board	*create_first_board(int size)
{
	t_board	*board;
	char	*tmp;

	board = (t_board *)malloc(sizeof(t_board));
	board->i = 0;
	board->size = size;
	board->array = (char *)malloc((board->size  + 1) * board->size * sizeof(char));
	tmp = board->array;
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

t_blocks *save_tetris(char* file_name, int num_tetris)
{
	int		fd;
	t_blocks	*blocks;
	char	*line;
	int		x;
	int		y;
	int		count;

	blocks = (t_blocks *)malloc(sizeof(t_blocks));
	fd = open(file_name, O_RDONLY);
	blocks->num = num_tetris;
	blocks->n = 0;
	y = 0;
	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		if (*line != '\0')
		{
			while (*line)
			{
				if (*line == '#')
				{
					blocks->x[blocks->n][count] = x;
					blocks->y[blocks->n][count] = y;
					count++;
				}
				line++;
				x++;
			}
			y++;
		}
		else
		{
			blocks->n++;
			y = 0;
			count = 0;
		}
	}
	blocks->n = 0;
	return (blocks);
}

int num_of_tetris(char *file_name)
{
	int num_tetris;
	char 	*line;
	int		fd;

	num_tetris = 1;
	fd = open(file_name,O_RDONLY);
	while(get_next_line(fd, &line) > 0)
	{
		if (*line == '\0')
			num_tetris++;
	}
	close(fd);
	return (num_tetris);
}

char *arraydup(char *array, int size)
{
	int		count;
	char	*new;
	char	*tmp;
	int		len;

	count = 0;
	len = size * 4 * (size + 1);
	new = (char *)malloc(sizeof(char) * len);
	tmp = new;
	while (count < len)
	{
		*tmp++ = *array++;
		count++;
	}
	return (new);
}

void	create_board(t_board *board)
{
	t_board *new;
	t_board	*tmp;

	tmp = board;
	new = (t_board *)malloc(sizeof(*new));
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->size = tmp->size;
	new->i = 0;
	new->j = 0;
	new->array = arraydup(tmp->array, tmp->size);
	new->next = NULL;
}

int	is_safe(t_board current, t_blocks blocks)
{
	int	count;

	count = 1;
	while (count < 4)
	{
		if (current.j + (blocks.x[blocks.n][count] - blocks.x[blocks.n][0]) < 0 || current.j + (blocks.x[blocks.n][count] - blocks.x[blocks.n][0]) >= current.size)
			return (0);
		if (current.i + (blocks.y[blocks.n][count] - blocks.y[blocks.n][0]) >= current.size)
			return (0);
		if (*(current.array + (current.i +  (blocks.y[blocks.n][count] - blocks.y[blocks.n][0])) * (current.size + 1) + (current.j +(blocks.x[blocks.n][count] - blocks.x[blocks.n][0]))) != '.')
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

int	new_linked_board(t_board *tmp, t_blocks *blocks, int j, int i)
{
	t_board *current;

	create_board(tmp);
	current = tmp;
	while(current->next != NULL)
		current = current->next;
	current->j = j;
	current->i = i;
	return (add_block(current, blocks));
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
void print_result(t_board *board)
{
	t_board *tmp;

	tmp = board;
	while (tmp->next != NULL)
		tmp = tmp->next;
	print_board(*tmp);
}
int	fillit(t_board *board, t_blocks *blocks, int j, int i)
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
			j= 0;
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

void solve(t_board *board, t_blocks *blocks)
{
	int	size;
	t_board	*new;

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

int	main(int argc, char **argv)
{
	char	*file_name;
	int		num_tetris;
	t_blocks	*pt_blocks;
	t_board		*pt_board;

	if (argc != 2)
		ft_putstr("usage: ./fillit file");
	file_name = argv[1];
	validate(file_name);
	num_tetris = num_of_tetris(file_name);
	pt_blocks = save_tetris(file_name, num_tetris);
	pt_board = create_first_board(square_size(num_tetris));
	solve(pt_board, pt_blocks);
	return (0);
}
