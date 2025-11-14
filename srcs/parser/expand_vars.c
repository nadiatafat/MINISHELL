/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:50:31 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/14 19:56:09 by sdossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_vars.h"
#include "expand_utils.h"
#include "lexer_utils.h"

/*
** Compte les tokens dans le tab pour l'expansion; le parcourt jusqu'au
** 1er pointeur NULL. Return le nb total de tokens à traiter.
*/
int	count_tokens_for_expansion(char **tokens)
{
	int	token_count;

	token_count = 0;
	while (tokens[token_count])
		token_count++;
	return (token_count);
}

static int	process_expanded_token(char **exp, int j, char *temp, int has_q)
{
	char	**split_result;
	int		k;

	if (!has_q && temp[0] && ft_strchr(temp, ' '))
	{
		split_result = ft_split(temp, ' ');
		if (split_result)
		{
			k = 0;
			while (split_result[k])
			{
				if (split_result[k][0])
					exp[j++] = ft_strdup(split_result[k]);
				k++;
			}
			free_tokens(split_result);
		}
		free(temp);
	}
	else if (temp[0])
		exp[j++] = temp;
	else
		free(temp);
	return (j);
}

/*
** Expanse les tokens d'un tab en appliquant les substitutions.
** Alloue 1 nouveau tab et traite chaque token individuellement.
** Return le tab expansé ou NULL en cas d'erreur.
*/
char	**expand_tokens(char **tokens, t_expand_ctx *ctx)
{
	char	**expanded;
	char	*temp;
	int		i;
	int		j;
	int		has_q;

	if (!tokens || !ctx)
		return (NULL);
	expanded = ft_calloc(sizeof(char *),
			(count_tokens_for_expansion(tokens) * 10) + 1);
	if (!expanded)
		return (NULL);
	i = -1;
	j = 0;
	while (tokens[++i])
	{
		has_q = (ft_strchr(tokens[i], '\'') || ft_strchr(tokens[i], '"'));
		temp = expand_token(tokens[i], ctx);
		if (!temp)
			return (free_tokens(expanded), NULL);
		j = process_expanded_token(expanded, j, temp, has_q);
	}
	expanded[j] = NULL;
	return (expanded);
}

/*
** Expanse un token unique en traitant les var qu'il contient.
** Gère les tokens spé (commençant par \x01) et ceux sans var.
** Return token expansé ou NULL si erreur d'alloc.
*/
char	*expand_token(char *token, t_expand_ctx *ctx)
{
	char	*result;

	if (token && token[0] == '\x01')
		return (ft_strdup(token + 1));
	if (!token)
		return (NULL);
	result = ft_strdup(token);
	if (!result)
		return (NULL);
	return (process_token_variables(result, ctx));
}

/*
** Nettoie les marqueurs d'échappement \x02 d'une chaîne.
** Parcourt la chaîne et supprime tous les marqueurs trouvés.
*/
char	*clean_escape_markers(char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (result[i])
	{
		if (result[i] == '\x02')
			i++;
		else
			result[j++] = result[i++];
	}
	result[j] = '\0';
	return (result);
}

/*
** Traite une variable à position donnée et avance le curseur.
** Extrait nom, récupère valeur, fait remplacement et calcule nouvelle pos.
*
int	process_single_var(char **result, int i, t_expand_ctx *ctx)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;
	int		var_len;

	var_name = get_var_name(*result, i + 1);
	if (!var_name)
		return (i + 1);
	var_value = get_variable_value(var_name, ctx);
	var_len = ft_strlen(var_name) + 1;
	new_result = replace_variable(*result, i, var_len, var_value);
	if (new_result != *result)
	{
		free(*result);
		*result = new_result;
		i += ft_strlen(var_value);
	}
	else
		i++;
	free(var_name);
	free(var_value);
	return (i);
}*/
