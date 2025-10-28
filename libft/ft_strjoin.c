/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:18:28 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/10 02:48:05 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int s1_len, int s2_len)
{
	char	*newstr;
	char	*pstr;
	int		join_len;

	join_len = s1_len + s2_len + 1;
	newstr = (char *)malloc(join_len * sizeof(char));
	if (!newstr)
		return (NULL);
	pstr = newstr;
	if (s1)
	{
		while (s1_len--)
			*pstr++ = *s1++;
	}
	if (s2)
	{
		while (s2_len--)
			*pstr++ = *s2++;
	}
	*pstr = '\0';
	return (newstr);
}

/*char	*ft_strjoin(char *s1, char *s2, int s1_len, int s2_len)
{
	char		*newstr;
	size_t		len1;
	size_t		len2;
	size_t		i;

	if (!s1 || !s2)
		return (NULL);

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	newstr = malloc(len1 + len2 + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strjoin(char *s1, char *s2, int s1_len, int s2_len)
{
	char	*newstr;
	char	*pstr;
	int		join_len;

	join_len = s1_len + s2_len + 1;
	newstr = (char *)malloc(join_len * sizeof(char));
	if (!newstr)
		return (NULL);
	pstr = newstr;
	if (s1)
	{
		while (s1_len--)
			*pstr++ = *s1++;
		free(s1 - (pstr - newstr));
	}
	if (s2)
	{
		while (s2_len--)
			*pstr++ = *s2++;
	}
	*pstr = '\0';
	return (newstr);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char str1[] = "Hello";
    char str2[] = " world!";
    char *joined = ft_strjoin(str1, str2);
    printf("Joined string: %s\n", joined);
    free(joined);
    return 0;
}*/
