/*
** EPITECH PROJECT, 2017
** get_next_line.h
** File description:
** all includes for gnl
*/

#ifndef __GNL_H__
# define __GNL_H__

#include <unistd.h>
#include <stdlib.h>

# ifndef READ_SIZE
#  define READ_SIZE	512
# endif /* !READ_SIZE */

char	*get_next_line(int);

#endif /* !__GNL_H__ */
