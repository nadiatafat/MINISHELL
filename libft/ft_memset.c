/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:23:02 by sdossa            #+#    #+#             */
/*   Updated: 2025/07/18 14:20:12 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*sp;

	sp = (unsigned char *)s;
	while (n--)
	{
		*sp++ = (char)c;
	}
	return (s);
}

/*void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char str[20] = "Hello, world!";
    ft_memset(str, '*', 5);
    printf("Modified string: %s\n", str);
    return 0;
}*/
