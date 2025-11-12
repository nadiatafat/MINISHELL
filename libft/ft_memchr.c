/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:31:14 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/18 14:19:09 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*sp;

	sp = (unsigned char *)s;
	while (n--)
	{
		if (*sp == (unsigned char)c)
			return ((void *)sp);
		sp++;
	}
	return (NULL);
}

/*void	*ft_memchr(const void *mem, int c, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)mem;
	i = 0;
	while (i < size)
	{
		if (ptr[i] == (unsigned char)c)
			return (ptr + i);
		i++;
	}
	return (NULL);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char str[] = "Hello, world!";
    char *result = ft_memchr(str, 'o', 12);
    printf("First occurrence of 'o': %s\n", result);
    return 0;
}*/
