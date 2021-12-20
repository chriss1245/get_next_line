/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:23:15 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/16 14:42:22 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Creates a new string with  s1 concatenated s2 until the n first bytes of s2
 * */

#include "get_next_line.h"

void	ft_bzero(void	*s, unsigned int n)
{
	unsigned char	*s_;

	s_ = s;
	while (n > 0)
	{
		*s_ = 0;
		s_++;
		n--;
	}
}

size_t	ft_strlen(const	char *c)
{
	size_t	len;

	len = 0;
	while (c[len])
		len++;
	return (len);
}

int	ft_strnchr_idx(const char *s, char c)
{
	unsigned char	c_;
	size_t			i;

	i = 0;
	c_ = (unsigned char) c;
	while (s[i])
	{
		if (s[i] == c_)
			return (i);
		i++;
	}
	if (c_ == '\0')
		return (i);
	return (-1);
}

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned char	*dest_;
	unsigned char	*src_;

	dest_ = dest;
	src_ = (unsigned char *) src;
	if (dest == 0 && src == 0)
		return (dest);
	while (n > 0)
	{
		*dest_ = *src_;
		dest_++;
		src_++;
		n--;
	}
	return (dest);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t m, size_t n)
{
	unsigned int	len_s1;
	char			*c;
	size_t			i;
	size_t			j;

	len_s1 = ft_strlen(s1);
	c = malloc((len_s1 + n + 1) * sizeof(char));
	if (!c)
		return (0);
	i = 0;
	while (i < len_s1 && i < m)
	{
		c[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < n)
	{
		c[i + j] = s2[j];
		j++;
	}
	c[i + j] = 0;
	return (c);
}
