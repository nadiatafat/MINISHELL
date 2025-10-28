/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:53:23 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/10 02:42:00 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t size)
{
	char		*pstr;
	size_t		len;
	size_t		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (start >= len)
		return (ft_calloc(1, sizeof(char)));
	if (size > len - start)
		size = len - start;
	pstr = malloc(size + 1);
	if (!pstr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		pstr[i] = s[start + i];
		i++;
	}
	pstr[size] = '\0';
	return (pstr);
}

/*char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > (size_t)ft_strlen(s))
		return (ft_strdup(""));
	if (len > (size_t)ft_strlen(s + start))
		len = (size_t)ft_strlen(s + start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

#include <stdio.h>
int main() {
    char const s[] = "Hello, world!";
	unsigned int	start = 3;
	size_t	len = 5;
	char	*str;

	str = ft_substr(s, start, len);
	printf("%s\n", str);
    free(str);
    return 0;
 }*/
