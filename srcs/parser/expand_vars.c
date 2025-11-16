/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdossa <sdossa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:50:31 by sdossa            #+#    #+#             */
/*   Updated: 2025/11/16 18:28:41 by sdossa           ###   ########.fr       */
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

static int	check_has_quotes(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '"')
		|| ft_strchr(token, '\x02') || ft_strchr(token, '\x03')
		|| ft_strchr(token, '\x04'))
		return (1);
	return (0);
}

static int	process_token_loop(char **tokens, char **expanded,
	t_expand_ctx *ctx)
{
	char	*temp;
	int		i;
	int		j;
	int		has_q;

	i = -1;
	j = 0;
	while (tokens[++i])
	{
		has_q = check_has_quotes(tokens[i]);
		temp = expand_token(tokens[i], ctx);
		if (!temp)
			return (-1);
		j = process_expanded_token(expanded, j, temp, has_q);
	}
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
	int		j;

	if (!tokens || !ctx)
		return (NULL);
	expanded = ft_calloc(sizeof(char *),
			(count_tokens_for_expansion(tokens) * 10) + 1);
	if (!expanded)
		return (NULL);
	j = process_token_loop(tokens, expanded, ctx);
	if (j == -1)
		return (free_tokens(expanded), NULL);
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
		if (result[i] == '\x02' || result[i] == '\x03'
			|| result[i] == '\x04')
			i++;
		else
			result[j++] = result[i++];
	}
	result[j] = '\0';
	return (result);
}
