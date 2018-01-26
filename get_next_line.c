/*
** EPITECH PROJECT, 2017
** get_next_line.c
** File description:
** get a line and go to the next one
*/

#include "my.h"

char	*my_realloc(char *src, int size)
{
	int	i = 0;
	char	*tmp;

	if ((tmp = malloc(sizeof(char) * size + 1)) == NULL) {
		return (NULL);
	}
	while (src[i]) {
		tmp[i] = src[i];
		++i;
	}
	src[i] = '\0';
	free(src);
	return (tmp);
}

static char	*first_use(int	*ret, int *begin, int fd, char *buff)
{
	if ((buff = malloc(sizeof(char) * (READ_SIZE + 1))) == NULL) {
		return (NULL);
	}
	if ((*ret = read(fd, buff, READ_SIZE)) == -1) {
		return (NULL);
	}
	buff[*ret] = '\0';
	*begin = 1;
	return (buff);
}

static char	*other_uses(int *ret, int *i, char **buff, char *dest, int fd)
{
	int	j = 0;
	int	len = READ_SIZE;

	while ((*buff)[*i] != '\n' && *ret) {
		if ((*buff)[*i]) {
			dest[j] = (*buff)[*i];
			++*i;
			++j;
		} else {
			if ((*ret = read(fd, *buff, READ_SIZE)) == -1)
				return (NULL);
			(*buff)[*ret] = '\0';
			dest[j] = '\0';
			*i = 0;
			len += *ret;
			if ((dest = my_realloc(dest, len)) == NULL)
				return (NULL);
		}
	}
	dest[j] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static int	begin = 0;
	static char	*buff = NULL;
	static int	i = 0;
	static int	ret = 0;
	char		*dest = malloc(sizeof(char) * READ_SIZE + 1);

	if (dest == NULL)
		return (NULL);
	if (begin == 0) {
		if ((buff = first_use(&ret, &begin, fd, buff)) == NULL)
			return (NULL);
		buff[ret] = '\0';
	}
	if ((dest = other_uses(&ret, &i, &buff, dest, fd)) == NULL)
		return (NULL);
	++i;
	if (ret == 0) {
		free(dest);
		free(buff);
		return (NULL);
	}
	return (dest);
}
