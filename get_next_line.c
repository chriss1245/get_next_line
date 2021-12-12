/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanzano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:21:42 by cmanzano          #+#    #+#             */
/*   Updated: 2021/12/10 13:23:46 by cmanzano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	get_next_line(int fd)
{
	char buffer[BUFFER_SIZE];

	buffer[0] = 'c';
	buffer[1] = fd;
	return (buffer[0]);
}

int main()
{
	get_next_line(2);
	printf("%c", get_next_line(2));
}
