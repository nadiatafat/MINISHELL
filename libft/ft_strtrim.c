/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:47:04 by sdossa            #+#    #+#             */
/*   Updated: 2024/12/03 15:41:40 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	size_t		trim_len;
	char		*str_trim;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = s1 + ft_strlen(s1);
	while (end > start && ft_strchr(set, *(end - 1)))
		end--;
	trim_len = end - start;
	str_trim = (char *)malloc(trim_len + 1);
	if (!str_trim)
		return (NULL);
	ft_memcpy(str_trim, start, trim_len);
	str_trim[trim_len] = '\0';
	return (str_trim);
}

/*static int	is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim_str;

	if (!s1)
		return (NULL);
	if (!set)
	{
		trim_str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
		if (!trim_str)
			return (NULL);
		ft_strlcpy(trim_str, s1, ft_strlen(s1) + 1);
		return (trim_str);
	}
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_in_set(s1[end - 1], set))
		--end;
	trim_str = malloc(sizeof(char) * (end - start + 1));
	if (!trim_str)
		return (NULL);
	ft_strlcpy(trim_str, &s1[start], end - start + 1);
	return (trim_str);
}

#include <stdio.h>
#include "libft.h"

int main() {
    char str[] = "  \t\nHello, world! \n\t ";
    char *trimmed = ft_strtrim(str, " \n\t");
    printf("Trimmed string: '%s'\n", trimmed);
    free(trimmed);
    return 0;
}*/
