/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:31:54 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:48:36 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		*ps1;
	const unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned const char *)s2;
	while (n--)
	{
		if (*ps1 != *ps2)
			return ((int)(*ps1 - *ps2));
		ps1++;
		ps2++;
	}
	return (0);
}

/*int	ft_memcmp(const void *mem1, const void *mem2, size_t size)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *)mem1;
	ptr2 = (unsigned char *)mem2;
	i = 0;
	while (i < size)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char str1[] = "Hello";
    char str2[] = "Hellz";
    printf("Comparison result: %d\n", ft_memcmp(str1, str2, 5));
    return 0;
}*/
