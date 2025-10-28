/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:23:37 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:42:13 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	const unsigned char	*pstr;

	pstr = (const unsigned char *)src;
	pdst = (unsigned char *)dst;
	if (pdst < pstr)
	{
		while (len--)
			*pdst++ = *pstr++;
	}
	else
	{
		pdst += len;
		pstr += len;
		while (len--)
			*--pdst = *--pstr;
	}
	return (dst);
}

/*static void	ft_memmove_backward(unsigned char *dest,
		const unsigned char *src, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		--i;
		dest[i] = src[i];
	}
}

static void	ft_memmove_forward(unsigned char *dest,
		const unsigned char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;

	if (dest == src || n == 0)
		return (dest);
	pdest = (unsigned char *)dest;
	psrc = (const unsigned char *)src;
	if (pdest < psrc)
	{
		ft_memmove_forward(pdest, psrc, n);
	}
	else
	{
		ft_memmove_backward(pdest, psrc, n);
	}
	return (dest);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char str[] = "Hello, world!";
    ft_memmove(str + 7, str, 5);
    printf("After memmove: %s\n", str);
    return 0;
}*/
