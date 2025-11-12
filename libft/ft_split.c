/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:06:17 by sdossa            #+#    #+#             */
/*   Updated: 2025/09/08 07:00:20 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_array(char **result)
{
	int	i;

	if (!result)
		return ;
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static int	ft_count_word(const char *str, char c)
{
	int	count;
	int	in_word;

	in_word = 0;
	count = 0;
	while (*str)
	{
		if (*str == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*ft_copy_word(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static int	ft_split_string(const char *str, char c, char **result)
{
	int			i;
	const char	*start;

	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			start = str;
			while (*str && *str != c)
				str++;
			result[i] = ft_copy_word(start, str - start);
			if (!result[i])
				return (0);
			i++;
		}
		else
			str++;
	}
	return (1);
}

char	**ft_split(const char *str, char c)
{
	char	**result;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = ft_count_word(str, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!ft_split_string(str, c, result))
	{
		ft_free_array(result);
		return (NULL);
	}
	result[word_count] = (NULL);
	return (result);
}

/*static size_t	ft_countword(char const *s, char c)
{
	size_t	cntw;
	size_t	i;

	i = 0;
	if (!s[i])
		return (0);
	cntw = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			cntw++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (cntw);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	size_t	wleng;
	int		i;

	lst = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!s || !lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				wleng = ft_strlen(s);
			else
				wleng = ft_strchr(s, c) - s;
			lst[i++] = ft_substr(s, 0, wleng);
			s = s + wleng;
		}
	}
	lst[i] = NULL;
	return (lst);
}*/
/*
#include <stdio.c>
int main()
{
	int	i;
	char const	s[] = "Lorem-ipsum-dolor-sit-amet";
	char	c = '-';
	char	**res;

	res = ft_split(s, c);
	if (res)
	{
		i = 0;
		while (res[i])
		{
			printf("%s\n", res[i]);
			free(res[i]);
			i++;
		}
		free(res);
	}
	return (0);
}*/
