/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:42 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/18 13:38:06 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*update_str(char *s, char *buffer, int offset)
{
	char	*ns;

	ns = ft_strnjoin(s, buffer, ft_strlen(s), offset);
	free(s);
	ft_memcpy(buffer, buffer + offset, BUFFER_SIZE - offset);
	ft_bzero(buffer + BUFFER_SIZE - offset, offset);
	return (ns);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int		scanned;
	char		*s;
	char		*ns;
	int			aux;
	int			buffer_len;
	
	buffer_len = ft_strlen(buffer);
	aux = ft_strnchr_idx(buffer, '\n');
	s = (char *) malloc(1*sizeof(char));
	*s = 0;
 	if (aux > -1)
		return (update_str(s, buffer, aux + 1));
	s = update_str(s, buffer, ft_strlen(buffer));
	printf("s (%s)", s);
	scanned = read(fd, buffer, BUFFER_SIZE);
	aux = ft_strnchr_idx(buffer, '\n');
	if (scanned <= 0)
	{
		if (buffer_len > 0 && aux < 0)
			return (s);
		free(s);
		return (0);
	}
	while (aux < 0 && scanned == BUFFER_SIZE)
	{
		ns = ft_strnjoin(s, buffer, ft_strlen(s), BUFFER_SIZE);
		free(s);
		s = ns;
		scanned = read(fd, buffer, BUFFER_SIZE);
		aux = ft_strnchr_idx(buffer, '\n');
	}
	if (scanned < BUFFER_SIZE && scanned >= 0)
	{
		if (aux < 0)
		{
			ns = ft_strnjoin(s, buffer, ft_strlen(s), scanned);
			ft_bzero(buffer, BUFFER_SIZE);
			free(s);
			return(ns);
		}
		else
		{
			ft_bzero(buffer + scanned, BUFFER_SIZE - scanned);
			aux = ft_strnchr_idx(buffer, '\n');
		}
	}
	ns = ft_strnjoin(s, buffer, ft_strlen(s), (size_t) aux + 1);
	free(s);
	ft_memcpy(buffer, buffer + aux + 1, BUFFER_SIZE - aux - 1);
	ft_bzero(buffer + BUFFER_SIZE - aux -1, aux + 1);
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
	printf("%s", get_next_line(fd));
	
	close(fd);
}*/
