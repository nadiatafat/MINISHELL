/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:14:11 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/16 20:54:01 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_vars.h"
#include "expand_utils.h"
#include "lexer_utils.h"

/*
** Expanse les tokens d'un tab en appliquant les substitutions.
** Alloue 1 nouveau tab et traite chaque token individuellement.
** Return le tab expansé ou NULL en cas d'erreur.
*/
int	calculate_var_len_with_markers(char *str, int start, int var_name_len)
{
	int	len;
	int	count;

	len = 0;
	count = 0;
	while (str[start + len] && count < var_name_len)
	{
		if (str[start + len] == '\x04')
			len++;
		else
		{
			len++;
			count++;
		}
	}
	while (str[start + len] == '\x04')
		len++;
	return (len);
}

int	split_and_add_tokens(char **exp, int j, char *temp, int max)
{
	char	**split_result;
	int		k;

	split_result = ft_split(temp, ' ');
	if (split_result)
	{
		k = 0;
		while (split_result[k])
		{
			if (split_result[k][0])
			{
				if (j >= max)
				{
					free_tokens(split_result);
					free(temp);
					return (-1);
				}
				exp[j] = ft_strdup(split_result[k]);
				exp[j] = clean_escape_markers(exp[j]);
				j++;
			}
			k++;
		}
		free_tokens(split_result);
	}
	free(temp);
	return (j);
}

int	process_expanded_token(char **exp, int j, char *temp, int has_q, int max)
{
	int		has_marker;
	int		i;

	has_marker = 0;
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\x02' || temp[i] == '\x04')
			has_marker = 1;
		i++;
	}
	if (!has_q && !has_marker && temp[0] && ft_strchr(temp, ' '))
		return (split_and_add_tokens(exp, j, temp, max));
	else if (temp[0] || has_q)
	{
		if (j >= max)
		{
			free(temp);
			return (-1);
		}
		exp[j] = clean_escape_markers(temp);
		j++;
	}
	else
		free(temp);
	return (j);
}

/*
** Extrait le nom d'une var à partir d'une position donnée.
** Valide que le nom commence par 1 lettre ou '_' et contient des char alpha.
** Return le nom de la var ou NULL si format invalide.
*/
char	*get_var_name(char *str, int start)
{
	char	*special_case;
	int		len;
	int		dollar_in_quotes;

	if (!str || !str[start])
		return (NULL);
	dollar_in_quotes = (start >= 2 && str[start - 2] == '\x04');
	if (dollar_in_quotes && str[start] != '\x04')
		return (NULL);
	if (!dollar_in_quotes && str[start] == '\x04')
		return (ft_strdup(""));
	special_case = handle_special_var_cases(str, start);
	if (special_case)
		return (special_case);
	while (str[start] == '\x04')
		start++;
	if (!ft_isalpha(str[start]) && str[start] != '_')
		return (NULL);
	len = count_varname_len(str, start);
	return (extract_varname(str, start, len));
}

int	count_varname_len(char *str, int start)
{
	int	len;
	int	in_quotes;
	int	prev_was_marker;

	len = 0;
	in_quotes = (start > 0 && str[start - 1] == '\x04');
	prev_was_marker = in_quotes;
	while (str[start + len])
	{
		if (str[start + len] == '\x03')
			break ;
		if (str[start + len] == '\x04')
		{
			len++;
			prev_was_marker = 1;
		}
		else if (ft_isalnum(str[start + len]) || str[start + len] == '_')
		{
			if (in_quotes && !prev_was_marker)
				break ;
			len++;
			prev_was_marker = 0;
		}
		else
			break ;
	}
	return (len);
}

