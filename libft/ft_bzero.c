/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:24:05 by sdossa            #+#    #+#             */
/*   Updated: 2024/11/18 11:43:04 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}*/
/*
int main() {
    char i_array[11]   = "Hello World";

    size_t pos = 0;

    ft_bzero(i_array, 6);

    for(; pos < 11; pos++) {
        printf("%lu: %d\n", (pos + 1), i_array[pos]);
    }


    return 0;
}
*/
