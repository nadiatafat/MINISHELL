/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:29:52 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 16:46:11 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_crash_func(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
}

char	*ft_strrchr(const char *s, int c)
{
	char	*end;
	int		s_len;

	if (!s)
		ft_crash_func();
	s_len = ft_strlen(s);
	end = (char *)s + s_len;
	if (c == '\0')
		return ((char *)end);
	while (end >= s)
	{
		if (*end == (char)c)
			return (end);
		end--;
	}
	return (NULL);
}

/*char	*ft_strrchr(const char *string, int find)
{
	size_t	i;

	i = ft_strlen(string);
	if (string[i] == (char)find)
		return ((char *)&string[i]);
	while (i > 0)
	{
		if (string[i - 1] == (unsigned char)find)
			return ((char *)&string[i - 1]);
		--i;
	}
	return (NULL);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char *str = "Hello, world!";
    printf("Last occurrence of 'o': %s\n", ft_strrchr(str, 'o'));
    return 0;
}*/
