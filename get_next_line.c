/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:42 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/16 19:05:56 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int		scanned;
	char		*s;
	char		*ns;
	int			aux;

	aux = ft_strnchr_idx(buffer, '\n');
 	if (aux > -1)
	{
		s = ft_strnjoin(buffer, "", ft_strnchr_idx(buffer, '\n') + 1, 0);
		ft_memcpy(buffer, buffer + aux + 1, BUFFER_SIZE - aux -1);
		ft_bzero(buffer + BUFFER_SIZE - aux - 1, aux + 1);
		printf("\ts\n");

		return (s);
	}
	s = ft_strnjoin(buffer, "", ft_strnchr_idx(buffer, '\0') , 0);
	scanned = read(fd, buffer, BUFFER_SIZE);
	aux = ft_strnchr_idx(buffer, '\n');
	if (scanned <= 0)
	{
		free(s);
		return (0);
	}
	while ( aux < 0 && scanned > 0)
	{
		ns = ft_strnjoin(s, buffer, ft_strlen(s), BUFFER_SIZE);
		free(s);
		s = ns;
		scanned = read(fd, buffer, BUFFER_SIZE);
		aux = ft_strnchr_idx(buffer, '\n');
	}
	ns = ft_strnjoin(s, buffer, ft_strlen(s), (size_t) aux + 1);
	free(s);
	ft_memcpy(buffer, buffer + aux + 1, BUFFER_SIZE - aux - 1);
	ft_bzero(buffer + BUFFER_SIZE - aux -1, aux + 1);
	printf("\tns\n");
	return (ns);
}

/*
int main()
{
	int fd = open("lol", O_RDONLY);

	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	
	close(fd);
}*/
