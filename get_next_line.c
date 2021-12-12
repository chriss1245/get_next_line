/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:42 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/12 17:58:19 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> 

typedef struct s_fd_buffer
{
	char	**buffers;
	int		*fds;
}t_buffer;
char	*get_next_line(int fd)
{
	size_t bsize;
	size_t	scanned;
	char	*s;
	int		i;
	static t_buffer buffer;

	buffer.buffers = (char **) malloc( 5* sizeof(char *));
	buffer.buffers[0] = (char *) malloc(BUFFER_SIZE * sizeof(char));
	bsize = BUFFER_SIZE;
	scanned = read(fd, buffer.buffers[0], bsize);
	s = (char *) malloc((scanned + 1) * sizeof(char));
	i = 0;
	while (i < scanned)
	{
		s[i] = buffer.buffers[0][i];
		i++;
	}
	s[i] = 0;
	return (s);
}

int main()
{
	int fd = open("lol", O_RDONLY);

	printf("%s\n", get_next_line(fd));
}
