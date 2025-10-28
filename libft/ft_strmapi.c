/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:56:09 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 15:45:42 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		s_len;
	char	*res;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	res = (char *)malloc(s_len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[s_len] = '\0';
	return (res);
}

/*char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!s || !f)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

#include <stdio.h>
#include "libft.h"

char my_func(unsigned int i, char c) {
    return c + i;
}

int main() {
    char str[] = "abcd";
    char *result = ft_strmapi(str, my_func);
    printf("Result: %s\n", result);
    free(result);
    return 0;
}*/
