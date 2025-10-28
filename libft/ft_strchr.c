/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:27:59 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/08 07:05:23 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*char	*ft_strchr(const char *string, int find)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (char)find)
			return ((char *)&string[i]);
		i++;
	}
	if (string[i] == (char)find)
		return ((char *)&string[i]);
	return (NULL);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char *str = "Hello, world!";
    printf("First occurrence of 'o': %s\n", ft_strchr(str, 'o'));
    return 0;
}*/
