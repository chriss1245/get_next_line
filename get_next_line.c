/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:42 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/15 12:11:53 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	size_t		scanned;
	char		*s;
	char		*ns;
	int			aux;
	
	buffer[BUFFER_SIZE] = 0;
	aux = ft_strnchr_idx(buffer, '\n') + 1;
	s = (char *) malloc(1*sizeof(char));
	s[0] = 0;
	if (aux > 0)
	{
		ns = ft_strnjoin(s, buffer + aux, BUFFER_SIZE-aux);
		free(s);
		s = ns;
	}
	scanned = read(fd, buffer, BUFFER_SIZE);
	if (scanned <= 0)
	{
		free(s);
		return (0);
	}
	while (ft_strnchr_idx(buffer, '\n') < 0 && scanned > 0)
	{
		ns = ft_strnjoin(s, buffer, BUFFER_SIZE);
		free(s);
		s = ns;
		scanned = read(fd, buffer, BUFFER_SIZE);
	}
	if (scanned < 0)
	{
		return (s);
	}
	ns = ft_strnjoin(s, buffer, (size_t) (ft_strnchr_idx(buffer, '\n') + 1));
	free(s);
	return (ns);
}

int main()
{
	int fd = open("lol", O_RDONLY);

	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
}
