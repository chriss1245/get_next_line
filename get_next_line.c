/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:42 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/18 14:55:18 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static char	*update_str(char *s, char *buffer, int offset)
{
	char	*ns;

	ns = ft_strnjoin(s, buffer, ft_strlen(s), offset);
	free(s);
	ft_memcpy(buffer, buffer + offset, BUFFER_SIZE - offset);
	ft_bzero(buffer + BUFFER_SIZE - offset, offset);
	return (ns);
}

static char	*get_next_line_scan_error(char *s, int buffer_len)
{
	if (buffer_len > 0)
		return (s);
	free(s);
	return (0);
}

static char	*get_next_line_scan_finished(char *s, char *buffer, int scanned)
{
	int	idx;

	idx = ft_strnchr_idx(buffer, '\n');
	if (idx < 0)
	{
		s = update_str(s, buffer, scanned);
		ft_bzero(buffer, BUFFER_SIZE);
		return (s);
	}
	idx = ft_strnchr_idx(buffer, '\n');
	return (update_str(s, buffer, idx + 1));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			scanned;
	char		*s;
	int			aux;
	int			buffer_len;

	buffer_len = ft_strlen(buffer);
	aux = ft_strnchr_idx(buffer, '\n');
	s = ft_strnjoin("", "", 0, 0);
	if (aux > -1)
		return (update_str(s, buffer, aux + 1));
	s = update_str(s, buffer, buffer_len);
	scanned = read(fd, buffer, BUFFER_SIZE);
	aux = ft_strnchr_idx(buffer, '\n');
	if (scanned <= 0)
		return (get_next_line_scan_error(s, buffer_len));
	while (aux < 0 && scanned == BUFFER_SIZE)
	{
		s = update_str(s, buffer, BUFFER_SIZE);
		scanned = read(fd, buffer, BUFFER_SIZE);
		aux = ft_strnchr_idx(buffer, '\n');
	}
	if (scanned < BUFFER_SIZE && scanned >= 0)
		return (get_next_line_scan_finished(s, buffer, scanned));
	return (update_str(s, buffer, aux + 1));
}
