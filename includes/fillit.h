/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:27:24 by yxie              #+#    #+#             */
/*   Updated: 2019/07/02 15:11:44 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 200

typedef struct	s_blocks
{
	int	num;
	int	n;
	int	x[40][4];
	int	y[40][4];	
}				t_blocks;
typedef struct	s_board
{
	int				i;
	int				j;
	int				size;
	char			*str;
	struct s_board	*next;
}				t_board;
int				get_next_line(const int fd, char **line);
int				validate_input(char *file_name);
int				ft_strcmp(const char *s1, const char *s2);
char			**ft_strsplit(char const *s, char c);
char			*ft_strnew(size_t size);
char			*ft_strncpy(char *dest, const char *src, size_t n);
void			ft_putstr(char const *s);
void			ft_putchar(char c);
void			save_coordinates(t_blocks *blocks, int fd, int x, int y);
t_blocks		*create_blocks(char *file_name, int num_tetris);
t_board			*create_first_board(int size);
int				num_of_tetris(char *file_name);
int				square_size(int num_tetris);
void			print_board(t_board board);
void			print_result(t_board *board);
char			*copy_board(char *array, int size);
void			create_board(t_board *board);
int				is_safe(t_board current, t_blocks blocks);
void			place_block(t_board *current, t_blocks blocks);
int				add_block(t_board *current, t_blocks *blocks);
int				new_linked_board(t_board *tmp, t_blocks *blocks, int j, int i);
void			delete_last_block(t_board *board);
int				fillit(t_board *board, t_blocks *blocks, int j, int i);
void			solve(t_board *board, t_blocks *blocks);
#endif
