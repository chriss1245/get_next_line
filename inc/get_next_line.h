/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:24:17 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/20 19:03:46 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# define MAX_FD 4096
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		ft_strnchr_idx(const char *s, char c);
char	*ft_strnjoin(char const *s1, char const *s2, size_t m, size_t n);
size_t	ft_strlen2(char const *c);
void	ft_bzero2(void	*s, unsigned int n);
void	*ft_memcpy(void *dest, const void *src, unsigned int n);
#endif
