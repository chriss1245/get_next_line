/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:42 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/20 19:07:44 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_str(char *s, char *buffer, int offset)
{
	char	*ns;

	ns = ft_strnjoin(s, buffer, ft_strlen2(s), offset);
	free(s);
	ft_memcpy(buffer, buffer + offset, BUFFER_SIZE - offset);
	ft_bzero2(buffer + BUFFER_SIZE - offset, offset);
	return (ns);
}

static char	*get_next_line_scan_error(char *s, int buffer_len, \
		char **buffers, int fd)
{
	free(buffers[fd]);
	buffers[fd] = 0;
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
		ft_bzero2(buffer, BUFFER_SIZE);
		return (s);
	}
	idx = ft_strnchr_idx(buffer, '\n');
	return (update_str(s, buffer, idx + 1));
}

static char	*get_next_chunck(char *s, char **buffers, int fd, int *ibs)
{
	s = update_str(s, buffers[fd], BUFFER_SIZE);
	ibs[2] = read(fd, buffers[fd], BUFFER_SIZE);
	ibs[0] = ft_strnchr_idx(buffers[fd], '\n');
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*buffers[MAX_FD];
	char		*s;
	int			ibs[3];

	if (fd < 0)
		return (0);
	if (!buffers[fd])
	{
		buffers[fd] = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		ft_bzero2(buffers[fd], BUFFER_SIZE + 1);
	}
	ibs[1] = ft_strlen2(buffers[fd]);
	ibs[0] = ft_strnchr_idx(buffers[fd], '\n');
	s = ft_strnjoin("", "", 0, 0);
	if (ibs[0] > -1)
		return (update_str(s, buffers[fd], ibs[0] + 1));
	s = get_next_chunck(s, buffers, fd, &ibs[0]);
	if (ibs[2] <= 0)
		return (get_next_line_scan_error(s, ibs[1], buffers, fd));
	while (ibs[0] < 0 && ibs[2] == BUFFER_SIZE)
		s = get_next_chunck(s, buffers, fd, &ibs[0]);
	if (ibs[2] < BUFFER_SIZE && ibs[2] >= 0)
		return (get_next_line_scan_finished(s, buffers[fd], ibs[2]));
	return (update_str(s, buffers[fd], ibs[0] + 1));
}
