/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:27:24 by yxie              #+#    #+#             */
/*   Updated: 2019/06/27 17:09:55 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_blocks
{
	int	num;
	int	n;
	int	x[40][4];
	int	y[40][4];	
} t_blocks;
typedef struct s_board
{
	int		i;
	int		j;
	int		size;
	char	*array;
	struct s_board	*next;
}				t_board;


#endif
